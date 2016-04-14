/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

#ifndef __ctkDICOMBrowser_h
#define __ctkDICOMBrowser_h

// Qt includes 
#include <QItemSelection>
#include <QWidget>

#include "ctkDICOMWidgetsExport.h"

class ctkDICOMBrowserPrivate;
class ctkThumbnailLabel;
class QModelIndex;
class ctkDICOMDatabase;
class ctkDICOMTableManager;

/// \ingroup DICOM_Widgets
class CTK_DICOM_WIDGETS_EXPORT ctkDICOMBrowser : public QWidget
{
  Q_OBJECT
  Q_PROPERTY( ctkDICOMDatabase* database READ database )
  Q_PROPERTY( QString databaseDirectory READ databaseDirectory WRITE setDatabaseDirectory )
  Q_PROPERTY( QString destinationDICOMDirectory READ destinationDICOMDirectory WRITE setDestinationDICOMDirectory )
  Q_PROPERTY( QStringList tagsToPrecache READ tagsToPrecache WRITE setTagsToPrecache )
  Q_PROPERTY( bool displayImportSummary READ displayImportSummary WRITE setDisplayImportSummary )
  Q_PROPERTY( bool indexerCancelBtnVisibility READ indexerCancelBtnVisibility WRITE setIndexerCancelBtnVisibility )
  Q_PROPERTY( bool updateSchemaCancelBtnVisibility READ updateSchemaCancelBtnVisibility WRITE setUpdateSchemaCancelBtnVisibility )
  Q_PROPERTY( ctkDICOMTableManager* dicomTableManager READ dicomTableManager )

public:
  typedef QWidget Superclass;
  explicit ctkDICOMBrowser(QWidget* parent=0);
  virtual ~ctkDICOMBrowser();

  /// Directory being used to store the dicom database
  QString databaseDirectory() const;

  /// Destination directory where the DICOM structure is copied
  QString destinationDICOMDirectory() const;

  /// See ctkDICOMDatabase for description - these accessors
  /// delegate to the corresponding routines of the internal
  /// instance of the database.
  /// @see ctkDICOMDatabase
  void setTagsToPrecache(const QStringList tags);
  const QStringList tagsToPrecache();

  /// Updates schema of loaded database to match the one
  /// coded by the current version of ctkDICOMDatabase.
  /// Also provides a dialog box for progress
  void updateDatabaseSchemaIfNeeded();

  ctkDICOMDatabase* database();

  ctkDICOMTableManager* dicomTableManager();

  /// Option to show or not import summary dialog.
  /// Since the summary dialog is modal, we give the option
  /// of disabling it for batch modes or testing.
  void setDisplayImportSummary(bool);
  bool displayImportSummary();

  /// Options to show cancel buttons in the progress dialogs
  void setIndexerCancelBtnVisibility( bool in_visibility_flag );
  bool indexerCancelBtnVisibility() const;

  void setUpdateSchemaCancelBtnVisibility( bool in_visibility_flag );
  bool updateSchemaCancelBtnVisibility() const;

  /// Accessors to status of last directory import operation
  int patientsAddedDuringImport();
  int studiesAddedDuringImport();
  int seriesAddedDuringImport();
  int instancesAddedDuringImport();

public Q_SLOTS:
  void setDatabaseDirectory(const QString& directory);
  void setDestinationDICOMDirectory( QString const & destinationDirectory);
  void onFileIndexed(const QString& filePath);

  void openImportDialog();
  void openExportDialog();
  void openQueryDialog();
  void onRemoveAction();
  void onRepairAction();

  void onTablesDensityComboBox(QString);

  /// Import a directory - this is used when the user selects a directory
  /// from the Import Dialog, but can also be used externally to trigger
  /// an import (i.e. for testing or to support drag-and-drop)
  void onImportDirectory(QString directory);

  /// slots to capture status updates from the database during an 
  /// import operation
  void onPatientAdded(int, QString, QString, QString);
  void onStudyAdded(QString);
  void onSeriesAdded(QString);
  void onInstanceAdded(QString);

Q_SIGNALS:
  /// Emited when directory is changed
  void databaseDirectoryChanged(const QString&);
  /// Emited when query/retrieve operation has happened
  void queryRetrieveFinished();
  /// Emited when the directory import operation has completed
  void directoryImported();
  /// Emited when more then 1 study/series of the patient were imported
  void multipleSeriesImported( QString const & patientName );

protected:
    QScopedPointer<ctkDICOMBrowserPrivate> d_ptr;
protected Q_SLOTS:
    void onModelSelected(const QItemSelection&, const QItemSelection&);

    /// To be called when dialog finishes
    void onQueryRetrieveFinished();

private:
  Q_DECLARE_PRIVATE(ctkDICOMBrowser);
  Q_DISABLE_COPY(ctkDICOMBrowser);
};

#endif

#ifndef DLGMISSING_H
#define DLGMISSING_H

#include "ui_dlgmissing.h"
#include "preferences/usersettings.h"
#include "library/library.h"
#include "library/libraryview.h"
#include "library/trackcollection.h"
#include "controllers/keyboard/keyboardeventfilter.h"

class WTrackTableView;
class MissingTableModel;

class DlgMissing : public QWidget, public Ui::DlgMissing, public LibraryView {
    Q_OBJECT

  public:
    DlgMissing(QWidget* parent, UserSettingsPointer pConfig,
               Library* pLibrary, TrackCollection* pTrackCollection,
               KeyboardEventFilter* pKeyboard);
    ~DlgMissing() override;

    void onShow() override;
    bool hasFocus() const override;
    void onSearch(const QString& text) override;
    QString currentSearch();

  public slots:
    void clicked();
    void selectAll();
    void selectionChanged(const QItemSelection&, const QItemSelection&);

  signals:
    void trackSelected(TrackPointer pTrack);

  private:
    void activateButtons(bool enable);
    WTrackTableView* m_pTrackTableView;
    MissingTableModel* m_pMissingTableModel;
};

#endif //DLGMISSING_H

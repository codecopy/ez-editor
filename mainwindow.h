#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QTextDocument>

class QAction;
class QLabel;
class QCloseEvent;
class QFile;
class QIODevice;
//class QTextEdit;
class QPlainTextEdit;

class FindDialog;
class Notice;
class SystemTray;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

signals:
    void fileOpened(const QString &path);
    void fileUpdated(const QString &path);
    void fileCleared();

public slots:
    //! ע����ô˺���ǰ�ȵ���sureWhenAskForSave()
    void openFile(const QString &path);

protected slots:
    void newFile();
    void openFile();
    bool saveFile();    //�ɹ�����ʱ����true�����򷵻�false��
    bool saveAsFile();
    void openRecentFile();

    void find();
    void findString(const QString &str, QTextDocument::FindFlags options);
    void setAutoWrap(bool wrap);
    void selectFont();
    void addWeek();
    void addDate();
    void addTime();
    void changeAssociation(bool enable);
    void about();

    void textChanged();
    void selectionChanged();
    void updateEncode();

    virtual void closeEvent(QCloseEvent *event);
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);

//#ifdef _NOTICE
protected slots:
    void hideToTray();
    void showMainWidget();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
//#endif //_NOTICE

private:
    void createActions();
    void createMenus();
    void createStatusBar();

#ifdef _NOTICE
    void createSystemTray();
    void createNotice();
#endif //_NOTICE

    void readSettings();
    void writeSettings();

    /* ����ֵ��
     * ����û���ȷѡ���˱���򲻱��棬����true��
     * ���ѡ����ȡ��������false(����ѡ�񱣴����ȡ����ѡ�񱣴�·����)��
     */
    bool sureWhenAskForSave();

    bool openFileHelper(const QString &filepath);
    bool saveFileHelper(const QString &filepath);

    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);
    bool isUtf8File(QIODevice *file);

private:
    QStringList recentFiles;
    QString curFile;
    QString charset;

//    QTextEdit *textEdit;
    QPlainTextEdit *textEdit;
    FindDialog *findDialog;

    enum { MaxRecentFiles = 5 };
    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *findAct;
    QAction *selectAllAct;
    QAction *weekAct;
    QAction *dateAct;
    QAction *timeAct;
    QAction *wrapAct;
    QAction *fontAct;
    QAction *txtAct;
    QAction *aboutAct;

    QLabel *wordCountLabel;
    QLabel *selectCountLabel;
    QLabel *encodelaLabel;

#ifdef _NOTICE
    QAction *showAct;
    QAction *hideAct;

    SystemTray *systemTray;
    Notice *notice;

    bool isShowAbout;
#endif //_NOTICE
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotSetStatus( const QString &status );

private:
    Ui::MainWindow *ui;
    QLabel m_statusLabel;
};

#endif // MAINWINDOW_H

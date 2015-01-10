#include <QMessageBox>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize( this->size() );

    ui->statusBar->addPermanentWidget( &m_statusLabel, 1 );
    m_statusLabel.setText( "Press Space-key for start" );

    connect( ui->sceneWidget, SIGNAL( signalShowStatus( QString ) ),
             this, SLOT( slotSetStatus( QString ) ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotSetStatus( const QString &status )
{
    QStringList list = status.split( "/" );
    if ( list.size() != 2 ) {
        return;
    }
    size_t points = list[0].toInt();
    size_t maxPoints = list[1].toInt();
    m_statusLabel.setText( status );
    if ( points == maxPoints ) {
        QMessageBox::information( this, tr( "Congratulation" ), tr( "You won the game!" ) );
        m_statusLabel.setText( "Press Space-key for start" );
    }
}

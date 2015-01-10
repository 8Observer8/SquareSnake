#include <QMatrix4x4>
#include "Scene.h"
#include "Painter.h"

Scene::Scene( QWidget *parent ) :
    QOpenGLWidget( parent ),
    m_maxSize( m_game.snakeMaxSize() )
{
    this->setFocusPolicy( Qt::StrongFocus );

    connect( &m_timer, SIGNAL( timeout() ),
             this, SLOT( slotUpdate() ) );
}

void Scene::slotUpdate()
{
    Snake::Status status = m_game.status();

    switch( status ) {
        case Snake::LIVE:
            break;
        case Snake::INCREASED:
            sendStatus();
            break;
        case Snake::DEAD:
            m_game.newGame();
            sendStatus();
            break;
        case Snake::WIN:
            m_timer.stop();
            sendStatus();
            return;
    }

    m_game.tick();
    update();
}

void Scene::slotSnakeSize( size_t size )
{
    QString status = QString::number( size );
    //emit signalSetStatus( status );
}

void Scene::initializeGL()
{
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

    QOpenGLShader vShader( QOpenGLShader::Vertex );
    vShader.compileSourceFile( ":/Shaders/vShader.glsl" );

    QOpenGLShader fShader( QOpenGLShader::Fragment );
    fShader.compileSourceFile( ":/Shaders/fShader.glsl" );

    m_program.addShader( &vShader );
    m_program.addShader( &fShader );

    if ( !m_program.link() )
    {
        qWarning( "Error: unable to link a shader program" );
        return;
    }

    m_vertexAttr = m_program.attributeLocation( "vertexAttr" );
    m_colorAttr = m_program.attributeLocation( "colorAttr" );
    m_matrixUniform = m_program.uniformLocation( "matrix" );
}

void Scene::paintGL()
{
    // Clear the window with current clearing color
    glClear( GL_COLOR_BUFFER_BIT );

    if ( !m_program.bind() )
        return;

    QMatrix4x4 matrix;
    matrix.ortho( 0.0f, 200.0f, 200.0f, 0.0f, -1.0f, 1.0f );
    //matrix.translate( 0.0f, 0.0f, -0.5f );
    m_program.setUniformValue( m_matrixUniform, matrix );

    Painter p( &m_program, m_vertexAttr, m_colorAttr );

    if ( m_timer.isActive() ) {
        m_game.draw( p );
    }

    m_program.release();
}

void Scene::resizeGL( int w, int h )
{
    // Prevent a divide by zero
//    if( h == 0 ) {
//        h = 1;
//    }

    // Set Viewport to window dimensions
    glViewport( 0, 0, w, h );

//    // Reset coordinate system
//    glMatrixMode( GL_PROJECTION );
//    glLoadIdentity();

//    // Establish clipping volume (left, right, bottom, top, near, far)
//    glOrtho( 0, 200, 200, 0,
//              -1.0, 1.0);

//    glMatrixMode( GL_MODELVIEW );
//    glLoadIdentity();
}

void Scene::keyPressEvent( QKeyEvent *event )
{
    switch ( event->key() ) {
        case Qt::Key_Left:
            m_game.keyEvent( Snake::LEFT );
            break;
        case Qt::Key_Up:
            m_game.keyEvent( Snake::UP );
            break;
        case Qt::Key_Right:
            m_game.keyEvent( Snake::RIGHT );
            break;
        case Qt::Key_Down:
            m_game.keyEvent( Snake::DOWN );
            break;
        case Qt::Key_Space:
            m_game.newGame();
            sendStatus();
            m_timer.start( 100 );
            break;
    }
}

void Scene::sendStatus()
{
    size_t points = m_game.snakeSize();
    emit signalShowStatus( QString( "%1/%2" ).arg( points ).arg( m_maxSize ) );
}

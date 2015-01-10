#include "Painter.h"
#include <QDebug>

Painter::Painter( QOpenGLShaderProgram *program, int vertexAttr,
                  int colorAttr ) :
    m_program( program ),
    m_vertexAttr( vertexAttr ),
    m_colorAttr( colorAttr )
{
    m_verticesOfBar.resize( 18 );
    m_verticesOfCircle.resize( 18 );

    initGreenColor();
    initRedColor();
}

void Painter::bar( int x1, int y1, int x2, int y2 )
{
    // 0
    m_verticesOfBar[0] = x1;
    m_verticesOfBar[1] = y1;
    m_verticesOfBar[2] = 0;

    // 1
    m_verticesOfBar[3] = x1;
    m_verticesOfBar[4] = y2;
    m_verticesOfBar[5] = 0;

    // 2
    m_verticesOfBar[6] = x2;
    m_verticesOfBar[7] = y1;
    m_verticesOfBar[8] = 0;

    // 3
    m_verticesOfBar[9] = x2;
    m_verticesOfBar[10] = y1;
    m_verticesOfBar[11] = 0;

    // 4
    m_verticesOfBar[12] = x1;
    m_verticesOfBar[13] = y2;
    m_verticesOfBar[14] = 0;

    // 5
    m_verticesOfBar[15] = x2;
    m_verticesOfBar[16] = y2;
    m_verticesOfBar[17] = 0;

    draw( m_verticesOfBar, m_greenColor );
}

void Painter::circle( int x, int y, int radius )
{
    // 0
    m_verticesOfCircle[0] = x - radius;
    m_verticesOfCircle[1] = y;
    m_verticesOfCircle[2] = 0;

    // 1
    m_verticesOfCircle[3] = x;
    m_verticesOfCircle[4] = y + radius;
    m_verticesOfCircle[5] = 0;

    // 2
    m_verticesOfCircle[6] = x;
    m_verticesOfCircle[7] = y - radius;
    m_verticesOfCircle[8] = 0;

    // 3
    m_verticesOfCircle[9] = x;
    m_verticesOfCircle[10] = y - radius;
    m_verticesOfCircle[11] = 0;

    // 4
    m_verticesOfCircle[12] = x;
    m_verticesOfCircle[13] = y + radius;
    m_verticesOfCircle[14] = 0;

    // 5
    m_verticesOfCircle[15] = x + radius;
    m_verticesOfCircle[16] = y;
    m_verticesOfCircle[17] = 0;

    draw( m_verticesOfCircle, m_redColor );
}

void Painter::initGreenColor()
{
    m_greenColor.resize( 18 );

    for ( unsigned int i = 0, j = 0; i < 6; ++i )
    {
        m_greenColor[j++] = 0.0f;
        m_greenColor[j++] = 1.0f;
        m_greenColor[j++] = 0.0f;
    }
}

void Painter::initRedColor()
{
    m_redColor.resize( 18 );

    for ( unsigned int i = 0, j = 0; i < 6; ++i )
    {
        m_redColor[j++] = 1.0f;
        m_redColor[j++] = 0.0f;
        m_redColor[j++] = 0.0f;
    }
}

void Painter::draw( const std::vector<float> &vertices,
                    const std::vector<float> &colors)
{
    m_program->setAttributeArray( m_vertexAttr, vertices.data(), 3 );
    m_program->setAttributeArray( m_colorAttr, colors.data(), 3 );

    m_program->enableAttributeArray( m_vertexAttr );
    m_program->enableAttributeArray( m_colorAttr );

    glDrawArrays( GL_TRIANGLES, 0, 6 );

    m_program->disableAttributeArray( m_vertexAttr );
    m_program->disableAttributeArray( m_colorAttr );
}

#ifndef PAINTER_H
#define PAINTER_H

#include <QOpenGLShaderProgram>
#include <vector>

class Painter
{
public:
    Painter( QOpenGLShaderProgram *program, int vertexAttr,
             int colorAttr );

    void bar( int x1, int y1, int x2, int y2 );
    void circle( int x, int y, int radius );

    void initGreenColor();
    void initRedColor();

private:
    void draw( const std::vector<float> &vertices,
               const std::vector<float> &colors );

    QOpenGLShaderProgram *m_program;
    int m_vertexAttr;
    int m_colorAttr;

    std::vector<float> m_verticesOfBar;
    std::vector<float> m_verticesOfCircle;
    std::vector<float> m_greenColor;
    std::vector<float> m_redColor;
};

#endif // PAINTER_H

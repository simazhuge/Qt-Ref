#ifndef TRIANGLE_H
#define TRIANGLE_H


#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
class Triangle : public QOpenGLWidget , protected QOpenGLExtraFunctions
{
public:
    Triangle(QWidget *parent = 0);
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
};

#endif // TRIANGLE_H

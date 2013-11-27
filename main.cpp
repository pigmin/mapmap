// NOTE: To run, it is recommended not to be in Compiz or Beryl, they have shown some instability.

#include <iostream>
#include <QApplication>
#include <QtGui>
#include "Common.h"
#include "DestinationGLCanvas.h"
#include "SourceGLCanvas.h"

#define DEFAULT_WIDTH  800
#define DEFAULT_HEIGHT 600

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  if (!QGLFormat::hasOpenGL())
  {
    std::cerr << "This system has no OpenGL support" << std::endl;
    return 1;
  }

  SourceGLCanvas sourceCanvas;
  DestinationGLCanvas destinationCanvas(0, &sourceCanvas);

  QObject::connect(&sourceCanvas, SIGNAL(quadChanged()),
                   &destinationCanvas, SLOT(updateCanvas()));

  QObject::connect(&destinationCanvas, SIGNAL(quadSwitched()),
                   &sourceCanvas, SLOT(updateCanvas()));

  QSplitter splitter(Qt::Horizontal);
  splitter.addWidget(&sourceCanvas);
  splitter.addWidget(&destinationCanvas);

  sourceCanvas.setFocusPolicy(Qt::ClickFocus);
  destinationCanvas.setFocusPolicy(Qt::ClickFocus);

  splitter.setWindowTitle(QObject::tr("LibreMapping"));
  splitter.resize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
  splitter.show();

  Common::initializeLibremapper(sourceCanvas.width(), sourceCanvas.height());
  return app.exec();
}



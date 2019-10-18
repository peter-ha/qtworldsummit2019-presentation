#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QskObjectCounter.h>
#include <QskWindow.h>
#include <QskPageIndicator.h>

int main(int argc, char *argv[])
{
    QskObjectCounter counter( true );
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QskPageIndicator pageIndicator;
    pageIndicator.setCurrentIndex( 0 );
    pageIndicator.setCount( 5 );

    QskWindow window;
    window.addItem( &pageIndicator );
    window.resize( 640, 480 );
    window.show();

    return app.exec();
}

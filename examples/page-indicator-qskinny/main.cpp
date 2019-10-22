#include <QskWindow.h>
#include <QskTextLabel.h>
#include <QskSetup.h>

#include <QGuiApplication>

int main( int argc, char* argv[] )
{
    QGuiApplication app( argc, argv );

    auto* label = new QskTextLabel("bla");

    qskSetup->setSkin("");

    QskWindow window;
    //window.addItem( label );
    //window.resize( 600, 600 );
    window.show();

    return app.exec();
}

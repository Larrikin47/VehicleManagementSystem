/* #include <QApplication>
#include "loginwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    LoginWindow w;
    w.show();
    return app.exec();
}
*/

#include <QApplication>
#include "loginwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    LoginWindow login;
    login.show();
    return app.exec();
}

#include <QApplication>

#include "addressbook.h"

// ActiveQt is Windows-only, so we disable it on other platforms
#ifdef Q_OS_WIN
#include <QAxFactory>

QAXFACTORY_BEGIN("{2b2b6f3e-86cf-4c49-9df5-80483b47f17b}",
                 "{8e827b25-148b-4307-ba7d-23f275244818}")
QAXCLASS(AddressBook)
QAXTYPE(ABItem)
QAXFACTORY_END()
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
#ifdef Q_OS_WIN
    if (!QAxFactory::isServer()) {
        AddressBook addressBook;
        addressBook.show();
        return app.exec();
    }
    return app.exec();
#else
    AddressBook addressBook;
    addressBook.show();
    return app.exec();
#endif
}

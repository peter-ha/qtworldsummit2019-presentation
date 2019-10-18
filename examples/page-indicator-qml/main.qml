import QtQuick 2.9
import QtQuick.Window 2.5
import QtQuick.Controls 2.5

Window {
    visible: true
    width: 640
    height: 480
    PageIndicator {
        currentIndex: 0
        count: 5
    }
}

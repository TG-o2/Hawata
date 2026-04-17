import QtQuick
import QtWebView

Item {
    id: root
    property url mapUrl: "https://www.google.com/maps?q=36.8065,10.1815&z=12"

    WebView {
        anchors.fill: parent
        url: root.mapUrl
    }
}

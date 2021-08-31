import QtQuick 2.6

/*!
    \qmltype TAwesomeIcon
    \inqmlmodule QtQuick 2.6
    \brief Font Icon
    \since 5.9.x
    \ingroup qtquicktest

    has been supported to the latest version

    \code
    TAwesomeIcon{
        source:T2D.FA_apple
    }
    \endcode

    Theme ini file is configured to 'FA_apple'.
*/
Item {
    id:toou2d_awesomeicon
    width:  16;
    height: 16;

    property color  color;

    /*! \sa TAwesomeType */
    property alias source : content_text.text;

    Text {
        id:content_text
        anchors.fill: parent;
        enabled:          false;
        color:            toou2d_awesomeicon.color;
        font.family:      "fontawesome"
        font.pixelSize:   Math.max(toou2d_awesomeicon.width,toou2d_awesomeicon.height);
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment:   Text.AlignVCenter; 
    }

}

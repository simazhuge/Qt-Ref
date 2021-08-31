import QtQuick 2.0

//只能iocn,根据source来判断选择使用TAwesomelIcon 或者 TSVGIcon*/
/*! TODO */
Item {
    id:toou2d_icon

    property string source;
    property color  color;

    Loader{
        anchors.fill: parent;
        sourceComponent: {
            if(toou2d_icon.source.toLowerCase().indexOf(".svg") !== -1){
                return svgComponent;
            }
            return awesomeiconComponent;
        }
    }

    Component{
        id:awesomeiconComponent
        TAwesomeIcon{
            enabled: false;
            source: toou2d_icon.source;
            color:  toou2d_icon.color;
        }
    }

    Component{
        id:svgComponent
        TSVGIcon{
            enabled: false;
            source: toou2d_icon.source;
            color:  toou2d_icon.color;
        }
    }
}

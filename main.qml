import QtQuick 2.9
import QtQml 2.1
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.2

Window {
    id: main_window

    width: 900
    height: 600

    maximumWidth: 900
    maximumHeight: 600

    minimumWidth: 900
    minimumHeight: 600

    visible: true
    title: qsTr("Bacteries")

    property int repro_counter: 0 //for counting bacteries reproduction
    property int content_visor_id: 0//for id bacteries reproduction
    property string content_visor_gender: "" //for gender bacteries reproduction
    property int content_visor_x: 0 //for x coord bacteries reproduction
    property int content_visor_y: 0 //for y coord bacteries reproduction
    property int start: 0 //for start position to watch bacteries
    property int end: 0 //for end position to watch bacteries
    property int limit_watcher: 0 //to control reading by chunks
    property int counter_watcher: 0 //to control reading by chunks
    property int width_bacteries_area: 10 //width for bacteries
    property int height_bacteries_area: 10 //height for bacteries
    //backgrond for Layout
    Rectangle{
    x: 0
    y: 0
    width: controllersLayout.width + 50
    height: main_window.height + 50
    color: "#404040"
    opacity: 0.8
    }

    ColumnLayout
    {
    id: controllersLayout

    width: 100;
    x: 10
    y: 10

    spacing: 15
    //slider for number of bacteries
    Slider{
        id: cttSlider
        orientation: Qt.Vertical
        from: 0
        value: 5
        to: 50
        //label
        Text {
            id: sliderLabel
            text: qsTr("              %1").arg(Math.floor(cttSlider.value))
            color: "yellow"
            anchors.centerIn: cttSlider.handle
        }
    }

    //button generate
    Rectangle{
    id: buttonCreate

    radius: 50
    width: 52
    height: 52

    border.color: "pink"
    border.width: 1
    color: "transparent"

    Image {
        width: 52
        height: 52
        fillMode: Image.PreserveAspectCrop
        source: "qrc:/icons/generate_bacteria.png"
    }
    MouseArea{
    hoverEnabled: true
    anchors.fill: buttonCreate
    onClicked:
     //code for generation here ...
        Bacteria_Handler.generate_bacteries(Math.floor(cttSlider.value))

    onPressed:  buttonCreate.scale = 0.8
    onReleased: buttonCreate.scale = 1
    onHoveredChanged: {buttonCreate.scale = 0.9; cursorShape = Qt.PointingHandCursor}
    onExited: buttonCreate.scale = 1
    }
    }

    //button init
    Rectangle{
    id: buttonInit
    radius: 50
    width: 52
    height: 52
    border.width: 1
    border.color: "pink"
    color: "transparent"

    Image {
        width: 52
        height: 52
        fillMode: Image.PreserveAspectCrop
        source: "qrc:/icons/bacteria_init.png"
    }
    MouseArea{
    hoverEnabled: true
    anchors.fill: buttonInit
    onClicked: {
        //code for init here ....
        Bacteria_Handler.move_bacteries()
        bacteria_viwer.model = Math.floor(cttSlider.value)
    }
    onPressed: buttonInit.scale = 0.8
    onReleased: buttonInit.scale = 1
    onHoveredChanged: {buttonInit.scale = 0.9; cursorShape = Qt.PointingHandCursor}
    onExited: buttonInit.scale = 1
    }
    }

    //button stop
    Rectangle{
    id: buttonStop
    radius: 50
    width: 52
    height: 52
    border.color: "pink"
    border.width: 1
    color: "transparent"

    Image {
        width: 52
        height: 52
        fillMode: Image.PreserveAspectCrop
        source: "qrc:/icons/bacteria_stop.png"
    }
    MouseArea{
    hoverEnabled: true
    anchors.fill: buttonStop
    onClicked: {
        //code for init here ....
        Bacteria_Handler.stop_movment()
    }
    onPressed: buttonStop.scale = 0.8
    onReleased: buttonStop.scale = 1
    onHoveredChanged: {buttonStop.scale = 0.9; cursorShape = Qt.PointingHandCursor}
    onExited: buttonStop.scale = 1
    }
    }

    //bacteria stats
    Rectangle{
    width: controllersLayout.width - 10
    height: 100
    color: "transparent"
    radius: 10
//    opacity: 0.8
    border.width: 1
    border.color: "lightpink"

    Text {
        id: text_reproduction
        text: qsTr("gen: %1").arg(repro_counter >= 1000 ? Math.floor(repro_counter) / 1000 : repro_counter)
        color: "yellow"
        leftPadding: 5

        MouseArea{
        hoverEnabled: true
        anchors.fill: text_reproduction
        onHoveredChanged: {text_reproduction.color = "red"; cursorShape = Qt.PointingHandCursor}
        onExited: text_reproduction.color = "yellow"

        onClicked: {
            main_window.opacity = 0.5
            window_collided_bacteries.visible = true
        } //on click then open windows for bacteries

        }
    }
    }

    //setting button
    Rectangle{
        id: settings_button
        width: 52
        height: 52
        color: "transparent"

        MouseArea{
        hoverEnabled: true
        anchors.fill: settings
        onPressed: settings.scale = 0.8
        onReleased: settings.scale = 1
        onHoveredChanged: {settings.scale = 0.9; cursorShape = Qt.PointingHandCursor}
        onExited: settings.scale = 1

        onClicked: { main_window.opacity = 0.5; window_extra.visible = true }
        }

    Image {
        id: settings
        width: 32
        height: 32
        fillMode: Image.PreserveAspectCrop
        source: "qrc:/icons/settings.png"
    }
    }
    }//end of layout

//    rectangle for bacteries area
    Rectangle{
    id: areaBacteria
    anchors.left: controllersLayout.right
    width:  parent.width
    height: parent.height
    color: "#404040"
    }

//    model view with repeater
    Repeater{
        id: bacteria_viwer
//        model: 5
    delegate: Rectangle{
        id: rect_bacteries_area_itself
//    delegate
        width: Bacteria_Handler.bacteria_container[index] ? width_bacteries_area : 0
        height: Bacteria_Handler.bacteria_container_y[index] ? height_bacteries_area : 0
        radius: 50
        color: Bacteria_Handler.bacteria_properties[index] === 0 ? "yellow" : "lightgreen"
        //bacteria position
        x: Bacteria_Handler.bacteria_container[index] ? Bacteria_Handler.bacteria_container[index] : 0
        y: Bacteria_Handler.bacteria_container_y[index] ? Bacteria_Handler.bacteria_container_y[index] : 0
    }
    } //end of Repeater

    //connections from C++ side
    Connections{
    target: Bacteria_Handler

    onNew_bacteria_generated: {repro_counter++}
    }

    //window for extra options
    Window{
    id: window_extra
    visible: false
    modality: Qt.WindowModal
    opacity: 0.8
    width: 700
    height: 200
    color: "#c2c2d6"
    //slider for timer refresh
    Slider{
    id: slider_for_timer_refresh
    from: 1
    to: 10

    value: 10 //default value
                                        //on value change then set new timer refresh
    onValueChanged: Bacteria_Handler.set_to_time_refresh(Math.floor(slider_for_timer_refresh.value))

    Text {
        anchors.top: slider_for_timer_refresh.bottom
        x: 10

        text: qsTr("fast")
        color: "black"
    }
    Text {
        anchors.top: slider_for_timer_refresh.bottom
        x: slider_for_timer_refresh.width - 40

        text: qsTr("slow")
        color: "black"
    }
    } //end of slider

    //close button
    Rectangle{
        id: close_btn

        y: window_extra.height - 70
        x: window_extra.width - 100

        width: 52
        height: 52
        radius: 50
        border.width: 1
        border.color: "#ff8c00"
        color: "transparent"

//        Image {
//            width: 52
//            height: 52
//            anchors.centerIn: parent
//            fillMode: Image.PreserveAspectCrop
//            source: "qrc:/icons/close_icon7.jpeg"
//        }

        Text {
            anchors.centerIn: parent
            text: qsTr("X")
            font.italic: true
            font.pixelSize: 40
            color: "#ff8c00"
        }

        MouseArea{
        hoverEnabled: true
        anchors.fill: close_btn
        onPressed: close_btn.scale = 0.8
        onReleased: close_btn.scale = 1
        onHoveredChanged: {close_btn.scale = 0.9; cursorShape = Qt.PointingHandCursor}
        onExited: close_btn.scale = 1

        onClicked: { main_window.opacity = 1; window_extra.visible = false }
        }
    }

    //slider for bacteries size
    Slider{
    id: slider_bacteries_size

    x: slider_for_timer_refresh.x
    y: slider_for_timer_refresh.y + 80

    from: 1
    to: 80
    value: 10

    //text small for slider
    Text {
        text: qsTr("small")
        y: slider_for_timer_refresh.y + 40
        x: slider_bacteries_size.x + 10
        color: "black"
    }
    //text big for slider
    Text {
        text: qsTr("big")
        y: slider_for_timer_refresh.y + 40
        x: slider_bacteries_size.width - 40
        color: "black"
    }
    onValueChanged: {
        width_bacteries_area = Math.floor(slider_bacteries_size.value)
        height_bacteries_area = Math.floor(slider_bacteries_size.value)
    }
    }

    } //end of window extra

    //window to watch collided bacteries
    Window{
    id: window_collided_bacteries
    visible: false
    title: "Collided Bacteries"
    modality: Qt.WindowModal

    opacity: 0.8

    width: 1100
    height: 600

    color: "#404040"

             //ColumnLayout for labels controllers for history
             ColumnLayout{
             x: 20
             y: main_window.height / 2
//             opacity: 0.5
             //text for current repro
             Text {
                 id: history_current_repro
                 text: qsTr("current: %1").arg(end)
                 color: "yellow"
                 font.bold: true
                 font.pixelSize: 17
                 font.italic: true
                 font.family: "Times New Roman, Times, serif"
             }
             //text for total repro
             Text {
                 id: history_total_repro
                 text: qsTr("total: %1").arg(repro_counter)
                 color: "pink"
                 font.bold: true
                 font.pixelSize: 17
                 font.italic: true
                 font.family: "Times New Roman, Times, serif"
             }
             }
           //    model view using repeater
               Repeater{
                   id: bacteria_collided_viewer
           //        model: 5
               delegate: Rectangle{
           //    delegate
                   width: Bacteria_Handler.collided_bacteries_x[index] ? 10 : 0
                   height: Bacteria_Handler.collided_bacteries_y[index] ? 10 : 0

                   radius: 50

                   color: Bacteria_Handler.collided_bacterie_props[index] === 0 ? "yellow" : "lightgreen"

                   //bacteria position
                   x: Bacteria_Handler.collided_bacteries_x[index] ? Bacteria_Handler.collided_bacteries_x[index] : 0
                   y: Bacteria_Handler.collided_bacteries_y[index] ? Bacteria_Handler.collided_bacteries_y[index] : 0

                   property int id: Bacteria_Handler.container_bacteries_ids[index] ? Bacteria_Handler.container_bacteries_ids[index]  : 0//property to save bacteria ID

                   MouseArea{
                   anchors.fill: parent

                   hoverEnabled: true

                   onHoveredChanged: {
                       cursorShape = Qt.PointingHandCursor

                       content_visor_id = bacteria_collided_viewer.itemAt(index).id

                       content_visor_gender = bacteria_collided_viewer.itemAt(index).color

                       content_visor_x = bacteria_collided_viewer.itemAt(index).x
                       content_visor_y = bacteria_collided_viewer.itemAt(index).y

                       visor_rect.visible = true
                   }

                   onExited: visor_rect.visible = false
                   }
               }
               } //end of Repeater

               //visor for any bacterie in collided viewer
               Rectangle{
               id: visor_rect

               visible: false

               width: 120
               height: 90

               x: content_visor_x
               y: content_visor_y

               radius: 50
               opacity: 0.7

               color: content_visor_gender
               Text {
                   id: content_for_visor
                   anchors.centerIn: parent
                   text: qsTr("ID: %1\ngender: %2\ncoord x: %3\ncoord y: %4")
                   .arg(content_visor_id)
                   .arg(content_visor_gender == "#ffff00" ? "female":"male")
                   .arg(content_visor_x).arg(content_visor_y)
                    color: "black"
               }
               }

    //watch button for showing collided bacteries
    Rectangle{
        id: watch_btn

        y: window_collided_bacteries.height - 70
        x: window_collided_bacteries.width - 100

        width: 52
        height: 52
        radius: 50
        border.width: 1
        border.color: "#ff8c00"
        color: "transparent"

//        Image {
//            width: 52
//            height: 52
//            anchors.centerIn: parent
//            fillMode: Image.PreserveAspectCrop
//            source: "qrc:/icons/icon_watch3.png"
//        }

        Text {
            anchors.centerIn: parent
            text: qsTr(">")
//            font.italic: true
            font.pixelSize: 40
            color: "#ff8c00"
        }

        MouseArea{
        hoverEnabled: true
        anchors.fill: watch_btn
        onPressed: watch_btn.scale = 0.8
        onReleased: watch_btn.scale = 1
        onHoveredChanged: {watch_btn.scale = 0.9; cursorShape = Qt.PointingHandCursor}
        onExited: watch_btn.scale = 1

        onClicked: {
            bacteria_collided_viewer.model = 0
            bacteria_collided_viewer.model = 500 //Bacteria_Handler.collided_bacteries_length()

            function read_bacteries_by_chunk(){ //it will read bacteries by chunk of 500 bacteries per each iteration
                var operation = repro_counter / 500

                if(operation > 0) //only if > then 0 preceed with assign
                limit_watcher = operation

                if(operation === 2 || operation > 2){
                start = end

                    end = end + 500

                    if(end === repro_counter || end > repro_counter){
                    end = repro_counter;
                    return
                    }
                }

                else{
                limit_watcher = 0 //restarting values first
                counter_watcher = 0
                start = 0
                end = 0

                start = 0
                end = repro_counter
                limit_watcher = 1
                }
            }

            read_bacteries_by_chunk() //calling to split by chunks

            if(counter_watcher < limit_watcher) //only execute if more bacteries chunk available
            Bacteria_Handler.supervise_collided_bacteries(start, end)

            counter_watcher++
        }
        }
    }

    //close button for closing collided bacteries window
    Rectangle{
        id: close_collided_btn

        x: window_collided_bacteries.width - 200
        y: window_collided_bacteries.height - 70

        width: 52
        height: 52
        radius: 50
        border.width: 1
        border.color: "#ff8c00"
        color: "transparent"

//        Image {
//            width: 52
//            height: 52
//            anchors.centerIn: parent
//            fillMode: Image.PreserveAspectCrop
//            source: "qrc:/icons/close_icon7.jpeg"
//        }

        Text {
            anchors.centerIn: parent
            text: qsTr("X")
            font.italic: true
            font.pixelSize: 40
            color: "#ff8c00"
        }

        MouseArea{
        hoverEnabled: true
        anchors.fill: close_collided_btn
        onPressed: close_collided_btn.scale = 0.8
        onReleased: close_collided_btn.scale = 1
        onHoveredChanged: {close_collided_btn.scale = 0.9; cursorShape = Qt.PointingHandCursor}
        onExited: close_collided_btn.scale = 1

        onClicked: {
                bacteria_collided_viewer.model = 0
                window_collided_bacteries.visible = false
                main_window.opacity = 1

                limit_watcher = 0
                counter_watcher = 0
                start = 0
                end = 0
        }
        }
    }

    } //end of windows collided bacteries

} //end of main windows

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtMultimedia 5.8
import com.amin.classes 1.0

ApplicationWindow
{
    visible: true
    width: 640
    height: 480
    title: qsTr("CvQml")

    ImageProcessor
    {
        id: imgProcessor

        onImageProcessed:
        {
            imgViewer.setImage(image);
            imageDrawer.open()
        }
    }

    Camera
    {
        id: camera

        imageCapture
        {
            onImageSaved:
            {
                imgProcessor.processImage(path)
            }
        }
    }

VideoOutput
{
    source: camera
    anchors.fill: parent

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            camera.imageCapture.capture()
        }
    }

    Label
    {
        text: "Touch the screen to take a photo<br>and process it using OpenCV!"
        color: "red"
    }
}

    Drawer
    {
        id: imageDrawer
        width: parent.width
        height: parent.height

        ImageViewer
        {
            id: imgViewer
            anchors.fill: parent

            Label
            {
                text: "Swipe from right to left<br>to return to capture mode!"
                color: "red"
            }
        }
    }
}

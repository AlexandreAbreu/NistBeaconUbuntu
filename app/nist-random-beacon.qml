/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Alexandre Abreu
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

import QtQuick 2.0
import Ubuntu.Components 1.1
import Beacon 1.0

/*!
    \brief MainView with Tabs element.
           First Tab has a single Label and
           second Tab has a single ToolbarAction.
*/

MainView {
    // objectName for functional testing purposes (autopilot-qt5)
    objectName: "mainView"

    // Note! applicationName needs to match the "name" field of the click manifest
    applicationName: "com.ubuntu.developer.abreu-alexandre.nist-random-beacon"

    /*
     This property enables the application to change orientation
     when the device is rotated. The default is false.
    */
    //automaticOrientation: true

    // Removes the old toolbar and enables new features of the new header.
    useDeprecatedToolbar: false

    width: units.gu(100)
    height: units.gu(75)

    Page {
        title: "NIST Randomness Beacon"

        Item {
            anchors.fill: parent
            anchors.margins: units.gu(4)
            width: parent.width
            Column {
                id: result
                anchors.fill: parent
                Text {
                    id: version
                    text: ""
                    wrapMode: Text.Wrap
                    width: parent.width - parent.anchors.margins
                }
                Text {
                    id: frequency
                    text: ""
                    wrapMode: Text.Wrap
                    width: parent.width - parent.anchors.margins
                }
                Text {
                    id: timestamp
                    text: ""
                    wrapMode: Text.Wrap
                    width: parent.width - parent.anchors.margins
                }
                Text {
                    id: output
                    text: ""
                    wrapMode: Text.Wrap
                    width: parent.width - parent.anchors.margins
                }

                Rectangle {
                    border.width: 1
                    height: 1
                    color: "black"
                    width: parent.width
                    visible: false

                    Behavior on y { SmoothedAnimation { velocity: 200 } }
                }
            }


            Button {
                id: beaconButton
                text: "Beacon"
                onClicked: {
                    beaconButton.enabled = false
                    request.requestLatestBeacon();
                }
                gradient: UbuntuColors.greyGradient
                anchors.centerIn: parent
                Behavior on y { SmoothedAnimation { velocity: 200 } }
            }
        }

        NistBeaconRequest {
            id: request
            onBeaconRequestResult: {
                if (status === NistBeaconRequest.RequestSuccess) {
                    version.text = result.version
                    frequency.text = result.frequency
                    var d = new Date(result.timestamp*1000)
                    timestamp.text = d.toString()
                    output.text = result.output
                }
                beaconButton.enabled = true
            }
        }

        tools: ToolbarItems {
            ToolbarButton {
                action: Action {
                    text: "About"
                    iconSource: Qt.resolvedUrl("graphics/toolbarIcon@8.png")
                    onTriggered: print("About")
                }
            }
            locked: true
            opened: true
        }
    }
}


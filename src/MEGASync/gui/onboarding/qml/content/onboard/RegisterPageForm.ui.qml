import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Components 1.0 as Custom
import Common 1.0
import Onboarding 1.0

Rectangle {
    id: registerForm


    /*
     * Properties
     */
    property alias registerButton: registerButton
    property alias cancelButton: cancelButton

    property bool passwordError: false

    readonly property int re_password: Onboarding.OnboardEnum.PASSWORD + 1

    property var formData: (new Map([[Onboarding.OnboardEnum.EMAIL, email.textField.text], [Onboarding.OnboardEnum.PASSWORD, password.textField.text], [Onboarding.OnboardEnum.FIRST_NAME, firstName.textField.text], [Onboarding.OnboardEnum.LAST_NAME, lastName.textField.text], [re_password, repeatPassword.textField.text]]))


    /*
     * Component
     */
    color: Styles.backgroundColor

    ColumnLayout {
        id: formLayout

        spacing: 12
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            topMargin: 24
            leftMargin: 40
            rightMargin: 40
        }

        Custom.RichText {
            Layout.alignment: Qt.AlignCenter | Qt.AlignTop
            Layout.bottomMargin: 4
            font.pixelSize: 20
            text: qsTr("Create your [b]MEGA account[/b]")
        }

        RowLayout {

            Custom.TextField {
                id: firstName

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                placeholderText: qsTr("First name")
            }

            Custom.TextField {
                id: lastName

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignTop
                placeholderText: qsTr("Last name")
            }
        }

        Custom.TextField {
            id: email

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
            placeholderText: qsTr("Email")
        }

        Custom.PasswordTextField {
            id: password

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
            placeholderText: qsTr("Password")
            error: passwordError
        }

        Custom.PasswordTextField {
            id: repeatPassword

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop
            placeholderText: qsTr("Repeat password")
            error: passwordError
            showInformativeText: passwordError
            informativeText: qsTr("The password entered don’t match. Please try again.")
            informativeTextIcon: "images/eye.svg"
        }

        Custom.CheckBox {
            id: dataLossCheckBox

            Layout.fillWidth: true
            Layout.topMargin: 24
            richText.url: "http://www.stackoverflow.com/" //TODO: CHANGE LINK
            text: qsTr("I understand that if [b]I lose my password, I may lose my data[/b].
Read more about [a]MEGA’s end-to-end encryption.[/a]")
        }

        Custom.CheckBox {
            id: termsCheckBox

            Layout.fillWidth: true
            Layout.topMargin: 4
            richText.url: "http://www.stackoverflow.com/" //TODO: CHANGE LINK
            text: qsTr("I agree with MEGA [a]Terms of service.[/a]")
        }
    } // ColumnLayout -> formLayout

    RowLayout {
        id: buttonLayout

        spacing: 8
        anchors {
            right: parent.right
            bottom: parent.bottom
            rightMargin: 32
            bottomMargin: 24
        }

        Custom.Button {
            id: cancelButton

            text: qsTr("Cancel")
        }

        Custom.Button {
            id: loginButton

            text: qsTr("Login")
        }

        Custom.Button {
            id: registerButton

            primary: true
            iconRight: true
            iconSource: "../../../../../images/onboarding/arrow_right.svg"
            text: qsTr("Next")
        }
    } // RowLayout -> buttonLayout
}

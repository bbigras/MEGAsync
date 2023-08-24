pragma Singleton
import QtQuick 2.12

QtObject {

    readonly property var accountTypeFree: qsTr("Free")
    readonly property var accountTypeProI: qsTr("Pro I")
    readonly property var accountTypeProII: qsTr("Pro II")
    readonly property var accountTypeProIII: qsTr("Pro III")
    readonly property var accountTypeLite: qsTr("Pro Lite")
    readonly property var accountTypeBusiness: qsTr("Business")
    readonly property var accountTypeProFlexi: qsTr("Pro Flexi")
    readonly property var addFolder: qsTr("Add folder")
    readonly property var agreeTerms: qsTr("I agree with MEGA's [a]Terms of service[/a]")
    readonly property var backUp: qsTr("Back up")
    readonly property var backup: qsTr("Backup")
    readonly property var backupButtonDescription: qsTr("Data from your device will automatically and consistently back up to MEGA in real-time.")
    readonly property var backupConfirm: qsTr("Backup: Confirm")
    readonly property var backupFolders: qsTr("Backup Folders")
    readonly property var backupSelectFolders: qsTr("Backup: Select folders")
    readonly property var backupTo: qsTr("Backup to:")
    readonly property var cancel: qsTr("Cancel")
    readonly property var change: qsTr("Change")
    readonly property var changeFolder: qsTr("Change folder")
    readonly property var changeEmailBodyText: qsTr("Enter the new email address and click Resend. We will then send the verification email to this new email address for you to activate your account.")
    readonly property var changeEmailTitle: qsTr("Change your email address")
    readonly property var deviceName: qsTr("Device name")
    readonly property var deviceNameDescription: qsTr("Add the name of your device.")
    readonly property var deviceNameTitle: qsTr("Add device name")
    readonly property var confirm: qsTr("Confirm")
    readonly property var confirmBackupErrorDuplicated: qsTr("There is already a folder named \"\" in this backup")
    readonly property var confirmBackupErrorRemote: qsTr("A folder named \"\" already exists on your backups")
    readonly property var confirmBackupFoldersTitle: qsTr("Confirm folders to back up")
    readonly property var confirmEmailTitle: qsTr("Account created")
    readonly property var confirmEmailBodyText: qsTr("To activate your account, you need to verify your email address. We've sent you an email with a confirmation link. Click on the link to verify your email address, then you will be able to log in.")
    readonly property var confirmEmailBodyText2: qsTr("If you don't receive the email within 1 hour, contact [a]support@mega.nz[/a]")
    readonly property var confirmEmailChangeText: qsTr("If you have misspelled your email address, [a]change it here[/a].")
    readonly property var confirmPassword: qsTr("Confirm password")
    readonly property var done: qsTr("Done")
    readonly property var email: qsTr("Email")
    readonly property var errorConfirmPassword: qsTr("Please confirm your password")
    readonly property var errorEmptyPassword: qsTr("Enter your password")
    readonly property var errorName: qsTr("Please enter your name")
    readonly property var errorLastName: qsTr("Please enter your last name")
    readonly property var errorPasswordsMatch: qsTr("Passwords don't match. Check and try again.")
    readonly property var errorValidEmail: qsTr("Enter a valid email address")
    readonly property var finalStepBackup: qsTr("Your backup has been setup and selected data will automatically backup whenever the desktop app is running. You can view your syncs and their statuses under the Sync tab in Settings.")
    readonly property var finalStepBackupTitle: qsTr("Your backup is set up")
    readonly property var finalStepQuestion: qsTr("What else do you want do?")
    readonly property var finalStepSync: qsTr("Your sync has been set up and will automatically sync selected data whenever the MEGA Desktop App is running.")
    readonly property var finalStepSyncTitle: qsTr("Your sync has been set up")
    readonly property var firstName: qsTr("First name")
    readonly property var fullSyncButtonDescription: qsTr("Sync your entire MEGA with your local device.")
    readonly property var fullSync: qsTr("Full sync")
    readonly property var fullSyncDescription: qsTr("Sync your entire MEGA Cloud drive with a local device.")
    readonly property var forgotPassword: qsTr("Forgot password?")
    readonly property var setUpOptions: qsTr("Setup options")
    readonly property var choose: qsTr("Choose:")
    readonly property var welcomeToMEGA: qsTr("Welcome to MEGA")
    readonly property var lastName: qsTr("Last name")
    readonly property var login: qsTr("Log in")
    readonly property var loginTitle: qsTr("Log in to your [b]MEGA account[/b]")
    readonly property var next: qsTr("Next")
    readonly property var notNow: qsTr("Not now")
    readonly property var viewInSettings: qsTr("View in Settings")
    readonly property var password: qsTr("Password")
    readonly property var previous: qsTr("Previous")
    readonly property var rename: qsTr("Rename")
    readonly property var resend: qsTr("Resend")
    readonly property var selectAll: qsTr("[b]Select all[/b]");
    readonly property var selectBackupFoldersTitle: qsTr("Select folders to back up")
    readonly property var selectBackupFoldersDescription: qsTr("Selected folders will automatically back up to the cloud when the desktop app is running.")
    readonly property var selectLocalFolder: qsTr("Select a local folder")
    readonly property var selectMEGAFolder: qsTr("Select a MEGA folder")
    readonly property var selectiveSyncButtonDescription: qsTr("Sync selected folders in your MEGA with a local device.")
    readonly property var selectiveSyncDescription: qsTr("Sync specific folders in your MEGA Cloud drive with a local device.")
    readonly property var selectiveSync: qsTr("Selective sync")
    readonly property var setUpMEGA: qsTr("Set up MEGA")
    readonly property var signUp: qsTr("Sign up")
    readonly property var signUpTitle: qsTr("Create your [b]MEGA account[/b]")
    readonly property var availableStorage: qsTr("Available storage:")
    readonly property var syncButtonDescription: qsTr("Sync your device and MEGA and any changes will automatically and instantly apply to MEGA and vice versa.")
    readonly property var syncTitle: qsTr("Choose sync type")
    readonly property var sync: qsTr("Sync")
    readonly property var syncChooseType: qsTr("Sync: Choose type")
    readonly property var syncSetUp: qsTr("Sync set up")
    readonly property var twoFANeedHelp: qsTr("Problem with two-factor authentication?")
    readonly property var twoFASubtitle: qsTr("Enter the 6-digit code generated by your authenticator app.")
    readonly property var twoFATitle: qsTr("Continue with [b]two factor authentication[/b]")
    readonly property var understandLossPassword: qsTr("I understand that if [b]I lose my password, I may lose my data[/b]. Read more about [a]MEGA’s end-to-end encryption.[/a]")
    readonly property var statusLogin: qsTr("Logging in...")
    readonly property var statusFetchNodes: qsTr("Fetching file list...")
    readonly property var statusSignUp: qsTr("Creating account...")
    readonly property var status2FA: qsTr("Validating 2FA code...")
    readonly property var statusWaitingForEmail: qsTr("Waiting for email confirmation...")
    readonly property var cancelLoginTitle: qsTr("Stop logging in?")
    readonly property var cancelLoginBodyText: qsTr("Closing this window will stop you logging in.")
    readonly property var cancelLoginPrimaryButton: qsTr("Stop Loggin in")
    readonly property var cancelLoginSecondaryButton: qsTr("Don’t stop")
    readonly property var cancelAccount: qsTr("Cancel account")
    readonly property var passwordAtleast8Chars: qsTr("Password needs to be at least 8 characters")
    readonly property var passwordStrengthVeryWeak: qsTr("Password easily guessed")
    readonly property var passwordStrengthWeak: qsTr("Weak password")
    readonly property var passwordStrengthMedium: qsTr("Average password")
    readonly property var passwordStrengthGood: qsTr("Good password")
    readonly property var passwordStrengthStrong: qsTr("Strong password")
    readonly property var itsBetterToHave: qsTr("It’s better to have:")
    readonly property var upperAndLowerCase: qsTr("Upper and lower case letters")
    readonly property var numberOrSpecialChar: qsTr("At least one number or special character")
    readonly property var longerPassword: qsTr("A longer password")
    readonly property var minimum8Chars: qsTr("Enter a minimum of 8 characters.")
    readonly property var passwordEasilyGuessed: qsTr("Your password could be easily guessed. Try making it stronger.")
    readonly property var finalPageButtonBackup: qsTr("Automatically update your files from your computers to MEGA cloud. Backup items in MEGA cloud can't be modified or deleted from MEGA cloud.")
    readonly property var finalPageButtonSync: qsTr("Sync your files between your computers with MEGA cloud, any change from one side will apply to another side.")
    readonly property var letsGetYouSetUp: qsTr("Let's get you set up")
    readonly property var confirmEmailAndPassword: qsTr("Confirm your email and password")
    readonly property var accountWillBeActivated: qsTr("Once confirmed, your account will be activated.")

}

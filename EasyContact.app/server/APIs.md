# Designed APIs Protocol

## GET
- easycontact/getAllEmailInfo
get the info of all the emails in the server
recv data schema:
    ```json
    {
        id: String,
        Subject: String,
        sentTime: String,
        CC: [String],
        To: [String],
        From: String,
        Context: String,
        linkForAttaches: [String],
    }, {...}
    ```

- easycontact/getTodayEmailInfo
get the info of all the emails recv today in the server
recv data schema:
    ```json
    {
        id: String,
        Subject: String,
        sentTime: String,
        CC: [String],
        To: [String],
        From: String,
        Context: String,
        linkForAttaches: [String],
    }, {...}
    ```

- easycontact/getSelectedDateEmailsInfo MetaData: selected Date
get the info of the emails recv on selected date
recv data schema: 
    ```json
    {
        id: String,
        Subject: String,
        sentTime: String,
        CC: [String],
        To: [String],
        From: String,
        Context: String,
        linkForAttaches: [String],
    }, {...}
    ```

- easycontact/getSelectedEmailInfo MetaData: id
get the info of the email with selected id
recv data schema: 
    ```json
    {
        id: String,
        Subject: String,
        sentTime: String,
        CC: [String],
        To: [String],
        From: String,
        Context: String,
        linkForAttaches: [String],
    }
    ```

## POST

- easycontact/sendNewEmail MetaData: email info
send the email with info
data schema: 
sent data schema: 
    ```json
    {
        Subject: String,
        sentTime: String,
        CC: [String],
        To: [String],
        From: String,
        Context: String,
        linkForAttaches: [String],
    }
    ```

## PUT

- easycontact/replyEmail MetaData: email info
reply selected email with new email info
sent data schema: 
    ```json
    {
        repliedEmailId: String,
        Subject: String,
        sentTime: String,
        CC: [String],
        To: [String],
        From: String,
        Context: String,
        linkForAttaches: [String],
    }
    ```

## DELETE

- easycontact/deleteEmails MetaData: email ids
delete selected emails (Move into trash folder)
sent data schema:
    ```json
    {
        id: [String]
    }
    ```

- easycontact/realDeleteEmails MetaData: email ids
sent delete the emails in the trash folder (delete permanently)
    ```json
    {
        id: [String]
    }
    ```

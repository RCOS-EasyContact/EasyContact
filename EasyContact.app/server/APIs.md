# Designed APIs Protocol

## GET
- easycontact/getAllEmailInfo
get the info of all the emails in the server
recv data schema: [<br />
    &nbsp;&nbsp;{<br />
        &nbsp;&nbsp;&nbsp;&nbsp;id: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;Subject: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;sentTime: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;CC: [String],<br />
        &nbsp;&nbsp;&nbsp;&nbsp;To: [String],<br />
        &nbsp;&nbsp;&nbsp;&nbsp;From: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;Context: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;linkForAttaches: [String],<br />
    &nbsp;&nbsp;}, {...}<br />
]<br />

- easycontact/getTodayEmailInfo
get the info of all the emails recv today in the server
recv data schema: [<br />
    &nbsp;&nbsp;{<br />
        &nbsp;&nbsp;&nbsp;&nbsp;id: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;Subject: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;sentTime: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;CC: [String],<br />
        &nbsp;&nbsp;&nbsp;&nbsp;To: [String],<br />
        &nbsp;&nbsp;&nbsp;&nbsp;From: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;Context: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;linkForAttaches: [String],<br />
    &nbsp;&nbsp;}, {...}<br />
]<br />

- easycontact/getSelectedDateEmailsInfo MetaData: selected Date
get the info of the emails recv on selected date
recv data schema: [<br />
    &nbsp;&nbsp;{<br />
        &nbsp;&nbsp;&nbsp;&nbsp;id: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;Subject: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;sentTime: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;CC: [String],<br />
        &nbsp;&nbsp;&nbsp;&nbsp;To: [String],<br />
        &nbsp;&nbsp;&nbsp;&nbsp;From: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;Context: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;linkForAttaches: [String],<br />
    &nbsp;&nbsp;}, {...}<br />
]<br />

- easycontact/getSelectedEmailInfo MetaData: id
get the info of the email with selected id
recv data schema: [<br />
    &nbsp;&nbsp;{<br />
        &nbsp;&nbsp;&nbsp;&nbsp;id: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;Subject: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;sentTime: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;CC: [String],<br />
        &nbsp;&nbsp;&nbsp;&nbsp;To: [String],<br />
        &nbsp;&nbsp;&nbsp;&nbsp;From: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;Context: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;linkForAttaches: [String],<br />
    &nbsp;&nbsp;}<br />
]<br />

## POST

- easycontact/sendNewEmail MetaData: email info
send the email with info
data schema: 
sent data schema: [<br />
    &nbsp;&nbsp;{<br />
        &nbsp;&nbsp;&nbsp;&nbsp;Subject: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;sentTime: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;CC: [String],<br />
        &nbsp;&nbsp;&nbsp;&nbsp;To: [String],<br />
        &nbsp;&nbsp;&nbsp;&nbsp;From: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;Context: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;linkForAttaches: [String],<br />
    &nbsp;&nbsp;}<br />
]<br />

## PUT

- easycontact/replyEmail MetaData: email info
reply selected email with new email info
sent data schema: [<br />
    &nbsp;&nbsp;{<br />
        &nbsp;&nbsp;&nbsp;&nbsp;repliedEmailId: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;Subject: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;sentTime: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;CC: [String],<br />
        &nbsp;&nbsp;&nbsp;&nbsp;To: [String],<br />
        &nbsp;&nbsp;&nbsp;&nbsp;From: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;Context: String,<br />
        &nbsp;&nbsp;&nbsp;&nbsp;linkForAttaches: [String],<br />
    &nbsp;&nbsp;}<br />
]<br />

## DELETE

- easycontact/deleteEmails MetaData: email ids
delete selected emails (Move into trash folder)
sent data schema:
[
    {
        id: [String]
    }
]

- easycontact/realDeleteEmails MetaData: email ids
sent delete the emails in the trash folder (delete permanently)
[
    {
        id: [String]
    }
]

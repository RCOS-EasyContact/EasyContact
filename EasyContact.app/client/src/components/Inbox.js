import React, { Component } from "react";
import { InboxHtml } from "./templates/InboxHtml";
import ModalCompose from "./ModalCompose";
import ModalMessage from "./ModalMessage";
import messages from "../data/messages.json";

export class Inbox extends Component {
  constructor(props) {
    super(props);
    this.markRead = this.markRead.bind(this);
    this.doShow = this.doShow.bind(this);
    this.doDelete = this.doDelete.bind(this);
    this.doRecover = this.doRecover.bind(this);
    this.permaDelete = this.permaDelete.bind(this);
    this.toggleMark = this.toggleMark.bind(this);
    this.toggleMarkAll = this.toggleMarkAll.bind(this);
    this.deleteMarked = this.deleteMarked.bind(this);
    this.refreshMessages = this.refreshMessages.bind(this);
    this.deleteMessages = this.deleteMessages.bind(this);
    this.ModalMessage = React.createRef();
    this.ModalCompose = React.createRef();
    this.state = {
      initMessages: messages,
      messages: messages,
      selected: {},
      deleted: [],
      drafts: [], 
    };
  }

  markRead(idx) {
    /* mark this message as read */
    let messages = [...this.state.messages];
    messages[idx].read = true;
    this.setState({ messages });
  }

  markAsUnRead(idx){
     /* mark this message as unread */
     let messages = [...this.state.messages];
     messages[idx].read = false;
     this.setState({ messages });
  }

  doShow(idx) {
    this.markRead(idx);
    this.setState({
      selected: messages[idx],
    });
    /* open message in modal */
    this.ModalMessage.current.show();
  }


  doCompose(val) {
    /* open compose modal */
    this.ModalCompose.current.show(val);
  }

  toggleMark(idx) {
    let messages = [...this.state.messages];
    messages[idx].marked = messages[idx].marked ? 0 : 1;
    this.setState({ messages });
  }

  doDelete(idx) {
    let messages = [...this.state.messages];
    let deleted = [...this.state.deleted];
    /* append it to deleted */
    deleted.push(messages[idx]);
    /* remove the message at idx */
    messages.splice(idx, 1);
    this.setState({ messages, deleted });
  }

  toggleMarkAll() {
    let messages = [...this.state.messages];
    messages.map((v, k) => {
      return (v.marked = v.marked ? 0 : 1);
    });
    this.setState({ messages });
  }

  deleteMarked() {
    let messages = [...this.state.messages];
    let deleted = [...this.state.deleted];
    let temp_store_message_idx = [];

    for (let i = 0; i < messages.length; i++) {
      //console.log(messages[i]);
      if (messages[i].marked === undefined) {
        console.log("und");
      } else if (messages[i].marked === 1) {
        deleted.push(messages[i]);
        temp_store_message_idx.push(i);
      }
    }
    for (let temp = temp_store_message_idx.length - 1; temp >= 0; temp--) {
      console.log(temp_store_message_idx[temp]);
      messages.splice(temp_store_message_idx[temp], 1);
    }
    this.setState({ messages, deleted });
  }

  refreshMessages() {
    let initMessages = [...this.state.initMessages];
    let deleted = [...this.state.deleted];
    deleted = [];

    this.setState({ messages: initMessages,deleted });

  }

  deleteMessages(arr) {}

  saveAsDraft(form) {
    let drafts = [...this.state.drafts];
    drafts.push(form); 
    this.setState({ drafts });
  }

  doRecover(idx) {
    let messages = [...this.state.messages];
    let deleted = [...this.state.deleted];
    /* append it to message */
    messages.push(deleted[idx]);
    /* remove the deleted at idx */
    deleted.splice(idx, 1);
    this.setState({ messages, deleted });
  }

  permaDelete(idx) {
    let messages = [...this.state.messages];
    let deleted = [...this.state.deleted];
    /* remove the message at idx */
    deleted.splice(idx, 1);
    this.setState({ messages, deleted });
  }

  render() {
    return (
      <div>
        <InboxHtml parent={this} />
        <ModalCompose
          ref={this.ModalCompose}
          saveAsDraft={this.saveAsDraft.bind(this)}
          sendTo={this.state.selected.fromAddress}
        />
        <ModalMessage ref={this.ModalMessage} message={this.state.selected} />
      </div>
    );
  }
}

export default Inbox;

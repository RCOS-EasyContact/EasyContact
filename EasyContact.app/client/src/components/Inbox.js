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
      deleted: []
    };
  }

  markRead(idx) {
    /* mark this message as read */

  }

  doShow(idx) {
  
  }

  doCompose() {
   
  }

  toggleMark(idx) {
   
  }

  doDelete(idx) {
    
  }

  toggleMarkAll() {
   
  }

  deleteMarked() {
    
  }

  refreshMessages() {
   
  }

  deleteMessages(arr) {
    
  }

  render() {
    return (
      <div>
        <InboxHtml parent={this} />
        <ModalCompose sendTo={this.state.selected.fromAddress} />
        <ModalMessage ref={this.ModalMessage} message={this.state.selected} />
      </div>
    );
  }
}

export default Inbox;

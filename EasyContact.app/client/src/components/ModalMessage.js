import React from "react";
import jquery from "jquery";

export class ModalMessage extends React.Component {
  constructor(props) {
    super(props);
    this.show = this.show.bind(this);
  }

  show() {
    jquery(this.refs.messageModal).modal("show");
  }

  render() {
    return (
      <div
        id="messageModal"
        className="modal fade mt-0 mt-md-5"
        tabIndex="-1"
        role="dialog"
        aria-hidden="true"
        ref="messageModal"
      >
      </div>
    );
  }
}

export default ModalMessage;

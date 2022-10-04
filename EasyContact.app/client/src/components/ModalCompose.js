import React from "react";
import jquery from "jquery";

export class ModalCompose extends React.Component {
  constructor(props) {
    super(props);
    this.show = this.show.bind(this);
    this.state = {};
  }

  show(idx) {
    /* open message in modal */
    jquery(this.refs.composeModal).modal("show");
  }

  render() {
    return (
      <div
        id="composeModal"
        className="modal fade mt-0 mt-md-5"
        tabIndex="-1"
        role="dialog"
        aria-hidden="true"
        ref="composeModal"
      >
      </div>
    );
  }
}

export default ModalCompose;

import React from "react";
import jquery from "jquery";

export class ModalCompose extends React.Component {
  constructor(props) {
    super(props);
    this.show = this.show.bind(this);
    this.state = {
      form: {
        to: "", 
        subject: "", 
        body: "", 
      },
      show: false,
      showTip: false, 
    };
  }

  show(value) {
    /* open message in modal */
    jquery(this.refs.composeModal).modal("toggle"); 

    this.setState({ form: value || this.state.form }); 
  }

  formChange = (key, e) => {

    this.setState({ form: { ...this.state.form, [key]: e.target.value } });
  };

  saveAsDraft = () => {
    console.log(2222);

    if (Object.keys(this.state.form).every((e) => !this.state.form[e])) {
      this.setState({ showTip: true });
      setTimeout(() => {

        this.setState({ showTip: false });
      }, 6000);
      return;
    }

    this.props.saveAsDraft(this.state.form);
    jquery(this.refs.composeModal).modal("toggle"); 
    // jquery(this.refs.composeModal).css("display", "none");
    // jquery(".modal-backdrop").css("display", "none");
    this.setState({
      form: {
        to: "", 
        subject: "", 
        body: "", 
      },
    });
  };

  render() {
    const { form, showTip } = this.state; 
    return (
      <div
        className="modal fade"
        id="composeModal"
        data-backdrop="static"
        data-keyboard="false"
        tabindex="-1"
        aria-labelledby="staticBackdropLabel"
        aria-hidden="true"
        ref="composeModal"
      >
        <div className="modal-dialog" >
          <div className="modal-content" style={{width:'800px',height:'500px'}}>
            <div className="modal-body pt-5">
              <div className="">
                {showTip ? (
                  <div
                    className="alert alert-warning alert-dismissible fade show  w-50  m-auto"
                    role="alert"
                  >
                    you can not save empty form
                    <button
                      type="button"
                      className="close"
                      data-dismiss="alert"
                      aria-label="Close"
                    >
                      <span aria-hidden="true">&times;</span>
                    </button>
                  </div>
                ) : (
                  ""
                )}
                <div className=" mb-3"></div>
                <form className="form-horizontal pr-4">
                  <div className="form-group row">
                    <label
                      htmlFor="inputTo"
                      className="col-sm-2 control-label text-right"
                    >
                      To
                    </label>
                    <div className="col-sm-10">
                      <input
                        type="email"
                        className="form-control"
                        id="inputTo"
                        placeholder="To"
                        value={form.to}
                        onChange={(e) => this.formChange("to", e)}
                      />
                    </div>
                  </div>
                  <div className="form-group row">
                    <label
                      htmlFor="inputSubject"
                      className="col-sm-2 control-label text-right"
                    >
                      Subject
                    </label>
                    <div className="col-sm-10">
                      <input
                        type="text"
                        className="form-control"
                        id="inputSubject"
                        placeholder="Subject"
                        value={form.subject}
                        onChange={(e) => this.formChange("subject", e)}
                      />
                    </div>
                  </div>
                  <div className="form-group row">
                    <label
                      htmlFor="inputBody"
                      className="col-sm-2 control-label text-right"
                    >
                      Body
                    </label>
                    <div className="col-sm-10">
                      <textarea
                        className="form-control"
                        style={{height:'200px'}}
                        id="inputBody"
                        placeholder="Body"
                        value={form.body}
                        onChange={(e) => this.formChange("body", e)}
                      />
                    </div>
                  </div>
                </form>
              </div>
            </div>
            <div className="modal-footer">
              <button
                type="button"
                className="btn btn-link mb-2"
                onClick={this.saveAsDraft} 
                data-dismiss="modal"
              >
                Save as Draft
              </button>
              <button
                type="button"
                className="btn btn-secondary btn-outline-secondary mb-2"
                data-dismiss="modal"
              >
                Close
              </button>
              <button type="button" className="btn btn-primary mb-2">
                Send
              </button>
            </div>
          </div>
        </div>
      </div>
    );
  }
}

export default ModalCompose;

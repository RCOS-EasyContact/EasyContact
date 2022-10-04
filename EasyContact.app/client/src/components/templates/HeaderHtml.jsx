import React from "react";

export const HeaderHtml = () => {
  return (
    <header className="bg-danger">
      <div className="container">
        <div className="row">
          <div className="col-12 mx-auto py-2">
            <div className="card border-0 bg-transparent">
              <div className="card-body">
                <div className="row">
                  <div className="col-lg-auto col-4 mx-auto text-nowrap text-center px-3">
                    {/*<a href="http://themes.guide" target="_new">
                      <span className="fab fa-react display-1 text-white d-block mx-auto" />
                    </a>*/}
                  </div>
                  <div className="col-lg text-center text-lg-left">
                    <h1 className="font-weight-light d-inline">
                      <span className="text-white">Easy Contact</span>
                    </h1>
                    <h6>A working template with Bootstrap 4</h6>
                    
                  </div>
                  <div className="col-lg-3 text-lg-right text-center d-flex flex-lg-column flex-row justify-content-center">
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </header>
  );
};

export default HeaderHtml;

class WS extends WebSocket
{
  constructor(url, protocols) {
    super(url, protocols);
    this.attachListeners();
  }
  attachListeners()
  {
    for (let [event, listener] of Object.entries(this.listeners)) {
      let options = {}
      if (listener instanceof Array) {
        [listener, options] = listener
      }
      this.addEventListener(event, listener.bind(this), options)
    }
  }
  listeners = {
    open: _ => {},
    message: data => {
      console.log(JSON.parse(data.data))
    },
    close: _ => {},
    error: _ => {}
  }
}

export default WS

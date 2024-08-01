class customElement extends HTMLElement {
  static observedAttributes = ["foo"]
  constructor() {
    super()
  }
  attributeChangedCallback(attr, oldVal, newVal) {
    console.log(attr, oldVal, newVal)
  }
}

export default customElement

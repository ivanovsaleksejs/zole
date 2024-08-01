import Element   from 'element'
import state     from '../state.js'
import WS        from '../ws.js'

class Game extends Element
{
  name = 'game'
  elementClass = '/elements/customElement'
  children = {
    gameArea: {
      name: 'gamearea',
      elementClass: '/elements/customElement',
    }
  }
  bindings = {
    gameData: {
      set: val => console.log(val),
      get: async _ => await fetch('/ajax')
    }
  }
  ws = new WS('/game')
  postRender = {
    readState: async _ => {
      let resp = await this.gameData
      let responseObject = await resp.json()
      console.log(responseObject)
      let cmd = {
        cmd: "SETUSERNAME",
        name: "TEST"
      }
      this.ws.send(JSON.stringify(cmd))
      cmd = {
        cmd: "MAKEMOVE",
        card: "10"
      }
      this.ws.send(JSON.stringify(cmd))
    }
  }
}

export default Game

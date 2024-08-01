import element from 'element'
import state   from './state.js'
import Game    from './templates/game.js'

const initGame = _ =>
{
  state.game = new Game
  state.game.appendTo(state.root)
}

export { initGame }

#include <iostream>

static const char * INDEX_HTML =  R"(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <link rel="stylesheet" href="./style.css">
</head>
<body>
  <main>
    <div class="info">
      <h1>Chex::WebUI</h1> 
      <h2 id="status"></h2>
    </div>
    <div id="chess"></div>
  </main>
  <script src="./script.js" defer></script>
</body>
</html>)";

static const char * SCRIPT_JS = R"(
const chess = document.getElementById("chess");
const BOARD_SIZE = 8;

function getPieceType(p) {
    return ["PAWN", "BISHOP", "KING", "QUEEN", "KNIGHT", "ROOK", "NONE"].at(p);
}

function getColorType(p) {
    return ["BLACK", "WHITE", "GREY"].at(p);
}

function renderBoard(data) {
    chess.innerHTML = "";

    const parsed = data;
    let i = 0;
    for (const key in parsed) {
    const item = parsed[key];
    let cell = document.createElement("span");
    cell.setAttribute("data-loc", key.split('-').reverse().join("-"));

    const row = parseInt(key.split("-")[0]);
    const col = parseInt(key.split("-")[1]);

    cell.classList.add((row + col) % 2 === 0 ? "white" : "black");
    cell.classList.add("cell");
    cell.setAttribute("data-empty", false);

    if (item.state === "empty") {
        cell.setAttribute("data-empty", true);
        chess.appendChild(cell);
        continue;
    }

    const pieceType = getPieceType(item.piece.type),
        color = getColorType(item.piece.color);

    let piece;
    if (color === "BLACK" && pieceType === "ROOK") {
        piece = "&#9820;"; // Rook (Black)
    } else if (color === "WHITE" && pieceType === "ROOK") {
        piece = "&#9814;"; // Rook (White)
    } else if (color === "BLACK" && pieceType === "BISHOP") {
        piece = "&#9822;"; // Bishop (Black)
    } else if (color === "WHITE" && pieceType === "BISHOP") {
        piece = "&#9815;"; // Bishop (White)
    } else if (color === "BLACK" && pieceType === "KNIGHT") {
        piece = "&#9821;"; // Knight (Black)
    } else if (color === "WHITE" && pieceType === "KNIGHT") {
        piece = "&#9816;"; // Knight (White)
    } else if (color === "BLACK" && pieceType === "QUEEN") {
        piece = "&#9819;"; // Queen (Black)
    } else if (color === "WHITE" && pieceType === "QUEEN") {
        piece = "&#9813;"; // Queen (White)
    } else if (color === "BLACK" && pieceType === "KING") {
        piece = "&#9818;"; // King (Black)
    } else if (color === "WHITE" && pieceType === "KING") {
        piece = "&#9812;"; // King (White)
    } else if (color === "BLACK" && pieceType === "PAWN") {
        piece = "&#9823;"; // Pawn (Black)
    } else if (color === "WHITE" && pieceType === "PAWN") {
        piece = "&#9817;"; // Pawn (White)
    }

    let pieceElem = document.createElement("span");
    pieceElem.classList.add("piece");
    pieceElem.innerHTML = piece;
    cell.appendChild(pieceElem);

    cell.setAttribute("data-color", item.piece.color);
    chess.appendChild(cell);
    i++;
    }
    attachEventListeners();
}

window.selected = null;

function attachEventListeners() {
    for (const elem of document.getElementsByClassName("cell")) {
        elem.addEventListener("click", async (event) => {
            let target = event.currentTarget,
                loc = target.getAttribute("data-loc");
                isEmpty = target.getAttribute("data-empty") === "true"

            if (!isEmpty && !window.selected) {
                target.classList.add("raised");
                window.selected = loc;
                return;
            }

            if (!isEmpty && window.selected === loc) {
                target.classList.remove("raised");
                window.selected = null;
                return;
            }

            if (window.selected && window.selected !== loc) {
                const raised = document.querySelector(`[data-loc="${window.selected}"]`);
                console.log(`move ${window.selected} to ${loc}`);

                const res = await fetch(`/move?m=${window.selected}.${loc}`);
                const moveStatus = await res.text();
                if (moveStatus === "bad move") {
                    setAlert("BAD MOVE!");
                } else {
                    target.innerHTML = raised.innerHTML;
                    raised.innerHTML = "";
                    raised.setAttribute("data-empty", true);
                    target.setAttribute("data-empty", false);
                }
                raised.classList.remove("raised");
                window.selected = null;
                return;
            }
        });
    }
}

const setStatus = (html) => {
    const elem = document.getElementById("status");
    elem.innerHTML = html;
};

const setAlert = (text) => {
    setStatus("<b style='color: red;font-weight: 800;'>" + text + "</b>");
    setTimeout(() => {
        setStatus("");
    }, 1500)
}

(async () => {
    const data = JSON.parse(`
{
  "0-0": {
    "state": "filled",
    "piece": {
      "type": 5,
      "color": 0,
      "position": {
        "x": 0,
        "y": 0
      }
    }
  },
  "0-1": {
    "state": "filled",
    "piece": {
      "type": 4,
      "color": 0,
      "position": {
        "x": 0,
        "y": 1
      }
    }
  },
  "0-2": {
    "state": "filled",
    "piece": {
      "type": 1,
      "color": 0,
      "position": {
        "x": 0,
        "y": 2
      }
    }
  },
  "0-3": {
    "state": "filled",
    "piece": {
      "type": 3,
      "color": 0,
      "position": {
        "x": 0,
        "y": 3
      }
    }
  },
  "0-4": {
    "state": "filled",
    "piece": {
      "type": 2,
      "color": 0,
      "position": {
        "x": 0,
        "y": 4
      }
    }
  },
  "0-5": {
    "state": "filled",
    "piece": {
      "type": 1,
      "color": 0,
      "position": {
        "x": 0,
        "y": 5
      }
    }
  },
  "0-6": {
    "state": "filled",
    "piece": {
      "type": 4,
      "color": 0,
      "position": {
        "x": 0,
        "y": 6
      }
    }
  },
  "0-7": {
    "state": "filled",
    "piece": {
      "type": 5,
      "color": 0,
      "position": {
        "x": 0,
        "y": 7
      }
    }
  },
  "1-0": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 0,
      "position": {
        "x": 1,
        "y": 0
      }
    }
  },
  "1-1": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 0,
      "position": {
        "x": 1,
        "y": 1
      }
    }
  },
  "1-2": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 0,
      "position": {
        "x": 1,
        "y": 2
      }
    }
  },
  "1-3": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 0,
      "position": {
        "x": 1,
        "y": 3
      }
    }
  },
  "1-4": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 0,
      "position": {
        "x": 1,
        "y": 4
      }
    }
  },
  "1-5": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 0,
      "position": {
        "x": 1,
        "y": 5
      }
    }
  },
  "1-6": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 0,
      "position": {
        "x": 1,
        "y": 6
      }
    }
  },
  "1-7": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 0,
      "position": {
        "x": 1,
        "y": 7
      }
    }
  },
  "2-0": {
    "state": "empty"
  },
  "2-1": {
    "state": "empty"
  },
  "2-2": {
    "state": "empty"
  },
  "2-3": {
    "state": "empty"
  },
  "2-4": {
    "state": "empty"
  },
  "2-5": {
    "state": "empty"
  },
  "2-6": {
    "state": "empty"
  },
  "2-7": {
    "state": "empty"
  },
  "3-0": {
    "state": "empty"
  },
  "3-1": {
    "state": "empty"
  },
  "3-2": {
    "state": "empty"
  },
  "3-3": {
    "state": "empty"
  },
  "3-4": {
    "state": "empty"
  },
  "3-5": {
    "state": "empty"
  },
  "3-6": {
    "state": "empty"
  },
  "3-7": {
    "state": "empty"
  },
  "4-0": {
    "state": "empty"
  },
  "4-1": {
    "state": "empty"
  },
  "4-2": {
    "state": "empty"
  },
  "4-3": {
    "state": "empty"
  },
  "4-4": {
    "state": "empty"
  },
  "4-5": {
    "state": "empty"
  },
  "4-6": {
    "state": "empty"
  },
  "4-7": {
    "state": "empty"
  },
  "5-0": {
    "state": "empty"
  },
  "5-1": {
    "state": "empty"
  },
  "5-2": {
    "state": "empty"
  },
  "5-3": {
    "state": "empty"
  },
  "5-4": {
    "state": "empty"
  },
  "5-5": {
    "state": "empty"
  },
  "5-6": {
    "state": "empty"
  },
  "5-7": {
    "state": "empty"
  },
  "6-0": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 1,
      "position": {
        "x": 6,
        "y": 0
      }
    }
  },
  "6-1": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 1,
      "position": {
        "x": 6,
        "y": 1
      }
    }
  },
  "6-2": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 1,
      "position": {
        "x": 6,
        "y": 2
      }
    }
  },
  "6-3": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 1,
      "position": {
        "x": 6,
        "y": 3
      }
    }
  },
  "6-4": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 1,
      "position": {
        "x": 6,
        "y": 4
      }
    }
  },
  "6-5": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 1,
      "position": {
        "x": 6,
        "y": 5
      }
    }
  },
  "6-6": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 1,
      "position": {
        "x": 6,
        "y": 6
      }
    }
  },
  "6-7": {
    "state": "filled",
    "piece": {
      "type": 0,
      "color": 1,
      "position": {
        "x": 6,
        "y": 7
      }
    }
  },
  "7-0": {
    "state": "filled",
    "piece": {
      "type": 5,
      "color": 1,
      "position": {
        "x": 7,
        "y": 0
      }
    }
  },
  "7-1": {
    "state": "filled",
    "piece": {
      "type": 4,
      "color": 1,
      "position": {
        "x": 7,
        "y": 1
      }
    }
  },
  "7-2": {
    "state": "filled",
    "piece": {
      "type": 1,
      "color": 1,
      "position": {
        "x": 7,
        "y": 2
      }
    }
  },
  "7-3": {
    "state": "filled",
    "piece": {
      "type": 3,
      "color": 1,
      "position": {
        "x": 7,
        "y": 3
      }
    }
  },
  "7-4": {
    "state": "filled",
    "piece": {
      "type": 2,
      "color": 1,
      "position": {
        "x": 7,
        "y": 4
      }
    }
  },
  "7-5": {
    "state": "filled",
    "piece": {
      "type": 1,
      "color": 1,
      "position": {
        "x": 7,
        "y": 5
      }
    }
  },
  "7-6": {
    "state": "filled",
    "piece": {
      "type": 4,
      "color": 1,
      "position": {
        "x": 7,
        "y": 6
      }
    }
  },
  "7-7": {
    "state": "filled",
    "piece": {
      "type": 5,
      "color": 1,
      "position": {
        "x": 7,
        "y": 7
      }
    }
  }} `)
    renderBoard(data);
})();
)";


static const char * STYLE_CSS = R"(
    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }
    main {
      position: absolute;
      top: 50%;
      left: 50%;
      transform: translate(-50%, -50%);
    }

    .info {
        display: flex;
        justify-content: space-between;
    }

    #chess {
      display: flex;
      flex-wrap: wrap;
      width: 560px;
    } 

    .cell {
      width: 70px;
      aspect-ratio: 1;
      user-select: none;
      cursor: pointer;;
      display: inline-block;
      position: relative;
    }
    .black {
      background-color: #b58863;
    }
    .black:hover {
      background-color: #7c5f43;
    }

    .white {
      background-color: #f0d9b5;
    }
    .white:hover {
      background-color: #ccac8c;
    }

    .raised {
      transform: scale(1.2);
      box-shadow: rgba(100, 100, 111, 0.2) 0px 7px 29px 0px;
      z-index: 999;
    }

    .piece {
      position: absolute;
      top: 50%;
      left: 50%;
      transform: translate(-50%, -50%);
      font-size: 45px;
    }
)";

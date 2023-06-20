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
        piece = "&#9820;";
    } else if (color === "WHITE" && pieceType === "ROOK") {
        piece = "&#9814;";
    } else if (color === "BLACK" && pieceType === "BISHOP") {
        piece = "&#9821;";
    } else if (color === "WHITE" && pieceType === "BISHOP") {
        piece = "&#9815;";
    } else if (color === "BLACK" && pieceType === "KNIGHT") {
        piece = "&#9822;";
    } else if (color === "WHITE" && pieceType === "KNIGHT") {
        piece = "&#9816;";
    } else if (color === "BLACK" && pieceType === "QUEEN") {
        piece = "&#9818;";
    } else if (color === "WHITE" && pieceType === "QUEEN") {
        piece = "&#9812;";
    } else if (color === "BLACK" && pieceType === "KING") {
        piece = "&#9819;";
    } else if (color === "WHITE" && pieceType === "KING") {
        piece = "&#9813;";
    } else if (color === "BLACK" && pieceType === "PAWN") {
        piece = "&#9823;";
    } else if (color === "WHITE" && pieceType === "PAWN") {
        piece = "&#9817;";
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

                    setPlayer(window.currentPlayer === "black" ? "white" : "black");
                    window.currentPlayer = window.currentPlayer === "black" ? "white" : "black";
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

const setPlayer = (color) => {
  setStatus(`${color}'s turn`);
}

const setAlert = (text) => {
    const elem = document.getElementById("status");
    let prev = elem.innerHTML;

    setStatus("<b style='color: red;font-weight: 800;'>" + text + "</b>");
    setTimeout(() => {
        setStatus(prev);
    }, 1500)
}

(async () => {
    const res = await fetch("/board");
    const data = await res.json();
    renderBoard(data);
    setPlayer("white");
})();
)";


static const char * STYLE_CSS = R"(
:root {
    --clr-black: #967259;
    --clr-white: #dbc1ac;
    --clr-bg: #38220f;
    --clr-text: #ffdc73;
}

* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    background: var(--clr-bg);
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
    align-items: center;
    font-family: Calisto MT, Bookman Old Style, Bookman, Goudy Old Style, Garamond, Hoefler Text, Bitstream Charter, Georgia, serif;
    margin-block: .3rem;
    color: var(--clr-text);
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
    cursor: pointer;
    display: inline-block;
    position: relative;
}
    .black {
      background-color: var(--clr-black);
    }
    .black:hover {
      background-color: #7c5f43;
    }

    .white {
      background-color: var(--clr-white);
    }
    .white:hover {
      background-color: #ccac8c;
    }

.raised {
    transform: scale(1.1);
    box-shadow: rgba(17, 17, 26, 0.1) 0px 4px 16px, rgba(17, 17, 26, 0.1) 0px 8px 24px, rgba(17, 17, 26, 0.1) 0px 16px 56px;
    z-index: 999;
    border-radius: 1px;
}

.piece {
    position: absolute;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    font-size: 45px;
}
)";

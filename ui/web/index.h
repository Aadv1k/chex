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
    chess.innerHTML = ""; // Clear the chessboard before re-rendering

    const parsed = data;
    let i = 0;
    for (const key in parsed) {
    const item = parsed[key];
    let cell = document.createElement("span");
    cell.setAttribute("data-loc", key);

    const row = parseInt(key.split("-")[0]);
    const col = parseInt(key.split("-")[1]);

    cell.classList.add((row + col) % 2 === 0 ? "white" : "black");
    cell.classList.add("cell");

    if (item.state === "empty") {
        cell.setAttribute("data-empty", null);
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

function attachEventListeners() {
    for (const elem of document.getElementsByClassName("cell")) {
    elem.addEventListener("click", async (event) => {
        const target = event.currentTarget;
        const isEmpty = target.getAttribute("data-empty");
        const loc = target.getAttribute("data-loc");
        const selected = getSelected();

        if (selected === loc) {
            elem.classList.remove("raised");
            setSelected(null);
            return;
        }

        console.log(selected, loc);
        if (selected && selected !== loc) {
        let data = await fetch(`/move?m=${selected.split("-").reverse().join("-")}.${loc.split("-").reverse().join("-")}`);
        let status = await data.text();

        if (status !== "done") {
            setStatus("<b style='color: red; font-weight: 800'>BAD MOVE!!</b>");
            setTimeout(() => {
                setStatus("");
            }, 1000);
            return;
        }
            let res = await fetch("/board");
            data = await res.json();
            elem.classList.remove("raised");
            renderBoard(data);
            attachEventListeners();
            return;
        }

        if (!isEmpty) {
        setSelected(loc);
        elem.classList.add("raised");
        return;
        }
    });
    }
}

const setSelected = (elem) => {
    if (!elem) {
      sessionStorage.removeItem("t");
      return;
    }
    sessionStorage.setItem("t", elem);
};

const setStatus = (html) => {
    const elem = document.getElementById("status");
    elem.innerHTML = html;
};

const getSelected = () => {
    return sessionStorage.getItem("t");
};

(async () => {
    sessionStorage.clear();
    let res = await fetch("/board");
    let data = await res.json();
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

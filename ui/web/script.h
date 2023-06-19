#define SCRIPT_JS R"(
const chess = document.getElementById("chess");
const BOARD_SIZE = 8;


function getPieceType(p) {
  return ["PAWN","BISHOP","KING","QUEEN","KNIGHT","ROOK","NONE"].at(p)
}

function getColorType(p) {
    return ["BLACK", "WHITE", "GREY"].at(p);
}


function renderBoard(data) {
    const parsed = JSON.parse(data);
    let i = 0;
    for (const key in parsed) {
        const item = parsed[key];
        let cell = document.createElement("span");
        cell.setAttribute("data-loc", key);


        const row = parseInt(key.split("-")[0]);
        const col = parseInt(key.split("-")[1]);
        cell.classList.add((row + col) % 2 === 0 ? "white" : "black");        cell.classList.add("cell");

        if (item.state === "empty") {
            cell.setAttribute("data-empty", null)
            chess.appendChild(cell);
            continue;
        }


        const pieceType = getPieceType(item.piece.type),
              color = getColorType(item.piece.color)

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
}

const setSelected = (elem) => {
    sessionStorage.setItem("t", elem);
}

const setStatus = (html) => {
    const elem = document.getElementById("status");
    elem.innerHTML = html;
}

const getSelected = () => {
    return sessionStorage.getItem("t");
}


for (const elem of document.getElementsByClassName("cell")) {
    elem.addEventListener("click", async (event) => {
        const target = event.currentTarget;
        const isEmpty = target.getAttribute("data-empty");
        const loc = target.getAttribute("data-loc");
        const selected = getSelected();

        if (selected === loc) {
            elem.classList.remove("raised");
            setSelected("")
            return;
        }

        if (selected && selected !== loc) {
            setStatus("<b style='color: red; font-weight: 800'>BAD MOVE!!</b>")
            setTimeout(() => {
                setStatus("")
            }, 1000);
            return;
        }

        if (!isEmpty) {
            setSelected(loc);
            elem.classList.add("raised");
            return;
        }


    })
}
)"

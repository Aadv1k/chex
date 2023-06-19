#define STYLES_CSS R"(
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
)"

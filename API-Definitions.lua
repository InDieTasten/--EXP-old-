"gui list"
-- "gui menu list"
-- "gui menu add {menuID}"
-- "gui menu remove {menuID}"
"gui menu access {menuID} list"
-- "gui menu access {menuID} property list"
-- "gui menu access {menuID} property {property} set {value}"
-- "gui menu access {menuID} property {property} get"
"gui menu access {menuID} action list"
"gui menu access {menuID} action {action} [args...]"
-- "gui menu access {menuID} element list"
-- "gui menu access {menuID} element add {elemID}"
-- "gui menu access {menuID} element remove {elemID}"
"gui menu access {menuID} element access {elemID} list"
"gui menu access {menuID} element access {elemID} property list"
-- "gui menu access {menuID} element access {elemID} property {property} set {value}"
-- "gui menu access {menuID} element access {elemID} property {property} get"
"gui menu access {menuID} element access {elemID} action list"
"gui menu access {menuID} element access {elemID} action {action} [args...]"
"gui dock list"
"gui dock add {dockItemID}"
"gui dock remove {dockItemID}"
"gui dock setTexture {dockItemID} {textureID}"
"gui dock getTexture {dockItemID}"
"level list"
"level add {solarID}"
"level remove {solarID}"
"level access {solarID} property list"
"level access {solarID} property {property} set {value}"
"level access {solarID} property {property} get"
"level access {solarID} action list"
"level access {solarID} action {action} [args...]"
"level access {solarID} object list"
"level access {solarID} object add {objID}"
"level access {solarID} object remove {objID}"
"level access {solarID} object access {objID} property list"
"level access {solarID} object access {objID} property {property} set {value}"
"level access {solarID} object access {objID} property {property} get"
"level access {solarID} object access {objID} action list"
"level access {solarID} object access {objID} action {action} [args...]"
"resource font list"
"resource font add {fontID}"
"resource font remove {fontID}"
"resource font access {fontID} property list"
"resource font access {fontID} property {property} set {value}"
"resource font access {fontID} property {property} get"
"resource font access {fontID} action list"
"resource font access {fontID} action {action} [args...]"
"resource texture list"
"resource texture add {textureID}"
"resource texture remove {textureID}"
"resource texture access {textureID} property list"
"resource texture access {textureID} property {property} set {value}"
"resource texture access {textureID} property {property} get"
"resource texture access {textureID} action list"
"resource texture access {textureID} action {action} [args...]"
"resource sound list"
"resource sound add {soundID}"
"resource sound remove {soundID}"
"resource sound access {soundID} property list"
"resource sound access {soundID} property {property} set {value}"
"resource sound access {soundID} property {property} get"
"resource sound access {soundID} action list"
"resource sound access {soundID} action {action} [args...]"
"resource track list"
"resource track add {trackID}"
"resource track remove {trackID}"
"resource track access {trackID} property list"
"resource track access {trackID} property {property} set {value}"
"resource track access {trackID} property {property} get"
"resource track access {trackID} action list"
"resource track access {trackID} action {action} [args...]"
"settings list"
"settings {setting} set {value}"
"settings {setting} get"


Menu-Properties:
	id
	title

	x
	y
	width
	height

	widthT
	heightT
	scrollX
	scrollY

	scrollable
	active
	visible

	borderColorA
	backgroundColorA
	titleBackgroundColorA
	titleTextColorA
	borderColorB
	backgroundColorB
	titleBackgroundColorB
	titleTextColorB

Element-Properties
	id
	type

	x
	y

	button
		width
		height

		displayText

		backgroundColorA
		borderColorA
		textColorA
		backgroundColorB
		borderColorB
		textColorB
		backgroundColorC
		borderColorC
		textColorC

		fontID
		textScale
	horSlider
		width
		height

		max
		min
		ratio
		value

		barBackgroundA
		barBorderA
		barBackgroundB
		barBorderB
		buttonBackgroundA
		buttonBorderA
		buttonBackgroundB
		buttonBorderB
		buttonBackgroundC
		buttonBorderC
		sliderBackgroundA
		sliderBorderA
		sliderBackgroundB
		sliderBorderB
		sliderBackgroundC
		sliderBorderC
		sliderBackgroundD
		sliderBorderD	
	label
		displayText

		textColorA
		textColorB
		textColorC

		fontID
		textScale
	textBox
		--nicht fertig
	vertSlider
		width
		height

		max
		min
		ratio
		value

		barBackgroundA
		barBorderA
		barBackgroundB
		barBorderB
		buttonBackgroundA
		buttonBorderA
		buttonBackgroundB
		buttonBorderB
		buttonBackgroundC
		buttonBorderC
		sliderBackgroundA
		sliderBorderA
		sliderBackgroundB
		sliderBorderB
		sliderBackgroundC
		sliderBorderC
		sliderBackgroundD
		sliderBorderD



canvas action clear
canvas action display
canvas action setFillColor {color}
canvas action setOutlineColor {color}
canvas action draw line {pos1.x} {pos1.y} {pos2.x} {pos2.y}
canvas action draw rect {pos1.x} {pos1.y} {pos2.x} {pos2.y}
canvas action draw ellipse {pos.x} {pos.y} {width} {height}


Color codes
0 dark black
1 dark blue
2 dark green
3 dark cyan
4 dark red
5 dark magenta
6 dark yellow
7 dark white
8 black
9 blue
a green
b cyan
c red
d magenta
e yellow
f white
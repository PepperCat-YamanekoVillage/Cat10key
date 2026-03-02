sort: _layout.json
	jq 'sort_by(.label | tonumber)' _layout.json > _sorted.json

conv: _sorted.json
	jq 'map(if .label then .matrix = (.label | split("") | map(tonumber)) | del(.label) else . end )' _sorted.json > _matrixed.json

compile:
	qmk compile -kb cat10key -km vial

flash:
	qmk flash -kb cat10key -km vial

console:
	qmk console

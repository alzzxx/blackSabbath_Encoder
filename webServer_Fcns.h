
void ServerEncoder::printHeader(EthernetClient client)
{
    /*
        This function sends to the client a standard html5 response header
    */

    client.println(F("HTTP/1.1 200 OK"));
    client.println(F("Content-Type: text/html"));
    client.println(F("Connection: close"));
    client.println();
    DEBUG_SERVERLN(F("Header sent!"));
}

void ServerEncoder::printPage(EthernetClient client)
{
    /*
        This function contains all the lines of the HTML code that displays the web server page
    */
    ServerEncoder::serverHeader(client);
    ServerEncoder::serverBody(client);
}

void ServerEncoder::serverHeader(EthernetClient client)
{
    client.println(F("<!-- Header -->"));
    client.println(F("<!DOCTYPE HTML>"));
    client.println(F("<html lang='en'>"));
    client.println(F("<head>"));
    client.println(F("<title>BESTduino parametrization</title>"));
    ServerEncoder::serverCSS(client);
    ServerEncoder::serverJavaScript(client);
    client.println(F("</head>"));
}

void ServerEncoder::serverCSS(EthernetClient client)
{
    client.println(F("<!-- CSS style -->"));
    client.println(F("<style>"));
    client.println(F("body {"));
    client.println(F("margin: 0;"));
    client.println(F("padding: 0;"));
    client.println(F("font-family: Roboto, helvetica, arial, sans-serif;"));
    client.println(F("line-height: 1.5em;"));
    client.println(F("color: #0b5c98;"));
    client.println(F("background-color: #eff4f9;"));
    client.println(F("}"));
    client.println(F("#grid-page {"));
    client.println(F("display: grid;"));
    client.println(F("grid-template-columns: 255px auto;"));
    client.println(F("grid-template-rows: 110px 768px auto;"));
    client.println(F("}"));
    client.println(F("#header {"));
    client.println(F("grid-column: 1 / span 2;"));
    client.println(F("background: #ffffff;"));
    client.println(F("}"));
    client.println(F("#header svg {"));
    client.println(F("margin: 0;"));
    client.println(F("padding-top: 10px;"));
    client.println(F("width: 235px;"));
    client.println(F("height: 85px;"));
    client.println(F("float: left;"));
    client.println(F("}"));
    client.println(F("#header h1 {"));
    client.println(F("margin: 0;"));
    client.println(F("position: relative;"));
    client.println(F("top: 50px;"));
    client.println(F("left: 0;"));
    client.println(F("text-align: center;"));
    client.println(F("font-size: xx-large;"));
    client.println(F("}"));
    client.println(F("#nav {"));
    client.println(F("float: left;"));
    client.println(F("background: #ffffff;"));
    client.println(F("color: #0b5c98;"));
    client.println(F("}"));
    client.println(F("#footer {"));
    client.println(F("grid-column: 1 / span 2;"));
    client.println(F("position: fixed;"));
    client.println(F("bottom: 0;"));
    client.println(F("clear: left;"));
    client.println(F("width: 100%;"));
    client.println(F("background: #bfe8f5;"));
    client.println(F("text-align: center;"));
    client.println(F("padding: 4px 0;"));
    client.println(F("}"));
    client.println(F("#content {"));
    client.println(F("float: left;"));
    client.println(F("margin-top: 30px;"));
    client.println(F("margin-left: 30px;"));
    client.println(F("margin-right: 30px;"));
    client.println(F("}"));
    client.println(F(".innertube {"));
    client.println(F("margin: 15px;"));
    client.println(F("/* Padding for content */"));
    client.println(F("margin-top: 0;"));
    client.println(F("}"));
    client.println(F("nav ul {"));
    client.println(F("text-align: center;"));
    client.println(F("list-style-type: none;"));
    client.println(F("margin: 0;"));
    client.println(F("padding: 0 30px;"));
    client.println(F("}"));
    client.println(F("nav ul a {"));
    client.println(F("text-align: center;"));
    client.println(F("color: #0b5c98;"));
    client.println(F("text-decoration: none;"));
    client.println(F("font-size: large;"));
    client.println(F("}"));
    client.println(F("nav ul a:hover {"));
    client.println(F("background-color: #0b5c98;"));
    client.println(F("color: #ffffff;"));
    client.println(F("}"));
    client.println(F(".buttons {"));
    client.println(F("column-span: all;"));
    client.println(F("}"));
    client.println(F("#grid_container_statuspage {"));
    client.println(F("display: grid;"));
    client.println(F("grid-template-columns: auto;"));
    client.println(F("grid-template-rows: repeat(4, auto);"));
    client.println(F("row-gap: 90px;"));
    client.println(F("}"));
    client.println(F("#grid_container_statuspage h2 {"));
    client.println(F("text-align: center;"));
    client.println(F("}"));
    client.println(F("#working_mode {"));
    client.println(F("display: grid;"));
    client.println(F("justify-content: center;"));
    client.println(F("}"));
    client.println(F("#working_mode p {"));
    client.println(F("text-align: center;"));
    client.println(F("}"));
    client.println(F("#grid_container_status {"));
    client.println(F("display: grid;"));
    client.println(F("grid-template-columns: repeat(6, auto);"));
    client.println(F("grid-template-rows: repeat(3, auto);"));
    client.println(F("justify-content: space-evenly;"));
    client.println(F("row-gap: 10px;"));
    client.println(F("}"));
    client.println(F("#grid_container_status div {"));
    client.println(F("font-weight: bold;"));
    client.println(F("font-size: small;"));
    client.println(F("text-align: center;"));
    client.println(F("}"));
    client.println(F("#grid_container_sensors {"));
    client.println(F("display: grid;"));
    client.println(F("grid-template-columns: repeat(2, auto);"));
    client.println(F("grid-template-rows: repeat(3, auto);"));
    client.println(F("justify-content: space-evenly;"));
    client.println(F("row-gap: 10px;"));
    client.println(F("}"));
    client.println(F("#restartbutton {"));
    client.println(F("display: grid;"));
    client.println(F("justify-content: center;"));
    client.println(F("}"));
    client.println(F(".dot_green {"));
    client.println(F("height: 25px;"));
    client.println(F("width: 25px;"));
    client.println(F("background-color: green;"));
    client.println(F("border-radius: 50%;"));
    client.println(F("display: inline-block;"));
    client.println(F("}"));
    client.println(F(".dot_red {"));
    client.println(F("height: 25px;"));
    client.println(F("width: 25px;"));
    client.println(F("background-color: red;"));
    client.println(F("border-radius: 50%;"));
    client.println(F("display: inline-block;"));
    client.println(F("}"));
    client.println(F("table.formdata {"));
    client.println(F("table-layout: fixed;"));
    client.println(F("overflow: hidden;"));
    client.println(F("border-collapse: collapse;"));
    client.println(F("width: 100%;"));
    client.println(F("margin: 1em 0 2em 0;"));
    client.println(F("}"));
    client.println(F("table.formdata th,"));
    client.println(F("td {"));
    client.println(F("text-align: center;"));
    client.println(F("border: 1px solid #c4cfda;"));
    client.println(F("margin: 0;"));
    client.println(F("padding: 0 5px;"));
    client.println(F("white-space: nowrap;"));
    client.println(F("}"));
    client.println(F("table.formdata th {"));
    client.println(F("background-color: #337dae;"));
    client.println(F("color: #ffffff;"));
    client.println(F("}"));
    client.println(F("table.formdata td {"));
    client.println(F("font-weight: lighter;"));
    client.println(F("background-color: white;"));
    client.println(F("}"));
    client.println(F(".description {"));
    client.println(F("overflow: scroll;"));
    client.println(F("}"));
    client.println(F("/* Scrollbar of descriptions */"));
    client.println(F("/* Dimensions */"));
    client.println(F(".description::-webkit-scrollbar {"));
    client.println(F("width: 0;"));
    client.println(F("height: 5px;"));
    client.println(F("}"));
    client.println(F("/* Track */"));
    client.println(F(".description::-webkit-scrollbar-track {"));
    client.println(F("background: #c8dbf5;"));
    client.println(F("}"));
    client.println(F("/* Handle */"));
    client.println(F(".description::-webkit-scrollbar-thumb {"));
    client.println(F("visibility: hidden;"));
    client.println(F("}"));
    client.println(F("/* Handle on hover */"));
    client.println(F(".description::-webkit-scrollbar-thumb:hover {"));
    client.println(F("visibility: visible;"));
    client.println(F("background: rgba(85, 85, 85, 0.575);"));
    client.println(F("}"));
    client.println(F("table.formdata caption {"));
    client.println(F("font-size: larger;"));
    client.println(F("font-weight: bolder;"));
    client.println(F("padding-bottom: 20px;"));
    client.println(F("}"));
    client.println(F(".codecol {"));
    client.println(F("width: 5rem;"));
    client.println(F("}"));
    client.println(F(".namecol {"));
    client.println(F("width: 9rem;"));
    client.println(F("}"));
    client.println(F(".namecol2 {"));
    client.println(F("width: 10rem;"));
    client.println(F("}"));
    client.println(F(".valuecol {"));
    client.println(F("width: 5rem;"));
    client.println(F("}"));
    client.println(F(".valuecol2 {"));
    client.println(F("width: 8rem;"));
    client.println(F("}"));
    client.println(F(".unitcol {"));
    client.println(F("width: 5rem;"));
    client.println(F("}"));
    client.println(F(".rwcol,"));
    client.println(F(".mincol,"));
    client.println(F(".maxcol {"));
    client.println(F("width: 5rem;"));
    client.println(F("}"));
    client.println(F(".desccol {"));
    client.println(F("width: 30rem;"));
    client.println(F("}"));
    client.println(F("table.formdata input,"));
    client.println(F("select {"));
    client.println(F("text-align: right;"));
    client.println(F("text-align-last: right;"));
    client.println(F("/* For the select element */"));
    client.println(F("width: 100%;"));
    client.println(F("border-style: none;"));
    client.println(F("}"));
    client.println(F("</style>"));
    client.println(F("<link rel='icon' href='data:,'>"));
}

void ServerEncoder::serverJavaScript(EthernetClient client)
{
    client.println(F("<!-- Javascript global variables and functions -->"));
    client.println(F("<script>"));
    client.println(F("var deviceID = 1;"));
    client.println(F("var localPort = 3000;"));
    client.println(F("var remotePort = 3000 + deviceID;"));
    client.println(F("var addressIP = [192, 168, 1, 20 + deviceID];"));
    client.println(F("var addressMAC = ['DE', 'AD', 'BE', 'EF', 'FE', 'ED'];"));
    client.println(F("var cameraRes;"));
    client.println(F("var flagAlert = 0;"));
    client.println(F("// getValuesFromArduino function. For assigning arduino variables values to the global variables used in javascript and in html -->  "));
    client.println(F("function getValuesFromArduino() {"));
    client.println(F("var request = new XMLHttpRequest();"));
    client.println(F("var parsedString, tempSection = [];"));
    client.println(F("request.onreadystatechange = function () {"));
    client.println(F("if (this.readyState == 4) {"));
    client.println(F("if (this.status == 200) {"));
    client.println(F("if (this.responseText != null) {"));
    client.println(F("parsedString = this.responseText.split('&');"));
    client.println(F("deviceID = parseInt(parsedString[0].split('=')[1]);"));
    client.println(F("remotePort = 3000 + deviceID;"));
    client.println(F("addressIP = [192, 168, 1, 20 + deviceID];"));
    client.println(F("localPort = parseInt(parsedString[1].split('=')[1]);"));
    client.println(F("for (var i = 0; i < 6; i++) {"));
    client.println(F("addressMAC[i] = parsedString[2].split('=')[1].split(':')[i];"));
    client.println(F("}"));
    client.println(F("document.getElementById('deviceID').value = deviceID;"));
    client.println(F("document.getElementById('deviceID').defaultValue = deviceID;"));
    client.println(F("document.getElementById('addressIP[0]').value = addressIP[0];"));
    client.println(F("document.getElementById('addressIP[0]').defaultValue = addressIP[0];"));
    client.println(F("document.getElementById('addressIP[1]').value = addressIP[1];"));
    client.println(F("document.getElementById('addressIP[1]').defaultValue = addressIP[1];"));
    client.println(F("document.getElementById('addressIP[2]').value = addressIP[2];"));
    client.println(F("document.getElementById('addressIP[2]').defaultValue = addressIP[2];"));
    client.println(F("document.getElementById('addressIP[3]').value = addressIP[3];"));
    client.println(F("document.getElementById('addressIP[3]').defaultValue = addressIP[3];"));
    client.println(F("document.getElementById('addressMAC[0]').value = addressMAC[0];"));
    client.println(F("document.getElementById('addressMAC[0]').defaultValue = addressMAC[0];"));
    client.println(F("document.getElementById('addressMAC[1]').value = addressMAC[1];"));
    client.println(F("document.getElementById('addressMAC[1]').defaultValue = addressMAC[1];"));
    client.println(F("document.getElementById('addressMAC[2]').value = addressMAC[2];"));
    client.println(F("document.getElementById('addressMAC[2]').defaultValue = addressMAC[2];"));
    client.println(F("document.getElementById('addressMAC[3]').value = addressMAC[3];"));
    client.println(F("document.getElementById('addressMAC[3]').defaultValue = addressMAC[3];"));
    client.println(F("document.getElementById('addressMAC[4]').value = addressMAC[4];"));
    client.println(F("document.getElementById('addressMAC[4]').defaultValue = addressMAC[4];"));
    client.println(F("document.getElementById('addressMAC[5]').value = addressMAC[5];"));
    client.println(F("document.getElementById('addressMAC[5]').defaultValue = addressMAC[5];"));
    client.println(F("document.getElementById('localPort').value = localPort;"));
    client.println(F("document.getElementById('localPort').defaultValue = localPort;"));
    client.println(F("document.getElementById('remotePort').value = remotePort;"));
    client.println(F("document.getElementById('remotePort').defaultValue = remotePort;"));
    client.println(F("for (var i = 3; i < parsedString.length; i++) {"));
    client.println(F("tempSection = parsedString[i].split('=');"));
    client.println(F("document.getElementById(tempSection[0]).value = parseInt(tempSection[1]);"));
    client.println(F("document.getElementById(tempSection[0]).defaultValue = parseInt(tempSection[1]);"));
    client.println(F("}"));
    client.println(F("cameraRes = parseFloat(document.getElementById('camRes').value);"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("request.open('GET', 'ajaxinitialize', true);"));
    client.println(F("request.send(null);"));
    client.println(F("}"));
    client.println(F("function loadPage() {"));
    client.println(F("getValuesFromArduino();"));
    client.println(F("document.getElementById(\"pages\").innerHTML = document.getElementById(\"deviceStatus\").innerHTML; "));
    client.println(F("}"));
    client.println(F("function parseDeviceID() {"));
    client.println(F("deviceID = parseInt(document.getElementById('deviceID').value);"));
    client.println(F("console.log(+deviceID);"));
    client.println(F("addressIP[3] = 20 + deviceID;"));
    client.println(F("remotePort = 3000 + deviceID;"));
    client.println(F("document.getElementById('addressIP[3]').value = addressIP[3];"));
    client.println(F("document.getElementById('remotePort').value = remotePort;"));
    client.println(F("}"));
    client.println(F("// clicked function. For the confirmation button in network paramenters submittion.   "));
    client.println(F("function clicked(e) {"));
    client.println(F("var changed = false;"));
    client.println(F("var element;"));
    client.println(F("element = document.getElementById('deviceID');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("element = document.getElementById('addressMAC[0]');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("element = document.getElementById('addressMAC[1]');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("element = document.getElementById('addressMAC[2]');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("element = document.getElementById('addressMAC[3]');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("element = document.getElementById('addressMAC[4]');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("element = document.getElementById('addressMAC[5]');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("element = document.getElementById('localPort');"));
    client.println(F("if (element.value != element.defaultValue) changed = true;"));
    client.println(F("if (changed) {"));
    client.println(F("if (!confirm('Attention: at least one of the Network Parameters has been changed, the device will be restarted. The webserver will be available at the following address: 192.168.1.' + addressIP[3] + '. Do you confirm?'))"));
    client.println(F("e.preventDefault();"));
    client.println(F("} else"));
    client.println(F("e.preventDefault();"));
    client.println(F("}"));
    client.println(F("// ajaxGet function. For sending parameters without refreshing page. Page is refreshed (or changed to new ip) if arduino needs to restart.  "));
    client.println(F("function ajaxGet(whichOne) {"));
    client.println(F("var data = new URLSearchParams();"));
    client.println(F("console.log('GET request done!');"));
    client.println(F("switch (whichOne) {"));
    client.println(F("case 'network':"));
    client.println(F("console.log('Net parameters sent!');"));
    client.println(F("data.append('deviceID', document.getElementById('deviceID').value);"));
    client.println(F("data.append('addressMAC[0]', document.getElementById('addressMAC[0]').value);"));
    client.println(F("data.append('addressMAC[1]', document.getElementById('addressMAC[1]').value);"));
    client.println(F("data.append('addressMAC[2]', document.getElementById('addressMAC[2]').value);"));
    client.println(F("data.append('addressMAC[3]', document.getElementById('addressMAC[3]').value);"));
    client.println(F("data.append('addressMAC[4]', document.getElementById('addressMAC[4]').value);"));
    client.println(F("data.append('addressMAC[5]', document.getElementById('addressMAC[5]').value);"));
    client.println(F("data.append('localPort', document.getElementById('localPort').value);"));
    client.println(F("break;"));
    client.println(F("case 'encoder':"));
    client.println(F("console.log('Encoder parameters sent!');"));
    client.println(F("if (document.getElementById('encDist').value)"));
    client.println(F("data.append('encDist', document.getElementById('encDist').value);"));
    client.println(F("if (document.getElementById('camRes').value) {"));
    client.println(F("cameraRes = parseFloat(document.getElementById('camRes').value);"));
    client.println(F("data.append('camRes', document.getElementById('camRes').value);"));
    client.println(F("}"));
    client.println(F("if (document.getElementById('patRes').value)"));
    client.println(F("data.append('patRes', document.getElementById('patRes').value);"));
    client.println(F("if (document.getElementById('inFilter').value)"));
    client.println(F("data.append('inFilter', document.getElementById('inFilter').value);"));
    client.println(F("if (document.getElementById('outFilter').value)"));
    client.println(F("data.append('outFilter', document.getElementById('outFilter').value);"));
    client.println(F("if (document.getElementById('tSample').value)"));
    client.println(F("data.append('tSample', document.getElementById('tSample').value);"));
    client.println(F("if (document.getElementById('patCurr').value)"));
    client.println(F("data.append('patCurr', document.getElementById('patCurr').value);"));
    client.println(F("}"));
    client.println(F("var xhr = new XMLHttpRequest();"));
    client.println(F("alert('Parameters updating procedure started. Do not change the parameters while this procedure is running. Thank you :) ');"));
    client.println(F("xhr.open('GET', data.toString());"));
    client.println(F("xhr.onload = function () { console.log(this.response) };"));
    client.println(F("xhr.send();"));
    client.println(F("if (whichOne == 'network') {"));
    client.println(F("refreshPage();"));
    client.println(F("}"));
    client.println(F("return false;"));
    client.println(F("}"));
    client.println(F("// function that refresh the page after 6 seconds.  "));
    client.println(F("function refreshPage() {"));
    client.println(F("setTimeout(function () {"));
    client.println(F("location.replace('http://' + addressIP[0] + '.' + addressIP[1] + '.' + addressIP[2] + '.' + addressIP[3]);"));
    client.println(F("}, 6000);"));
    client.println(F("}"));
    client.println(F("// function that is called every 5s to get from the arduino the diagnostic of the device  "));
    client.println(F("window.setInterval(function () {"));
    client.println(F("nocache = '&nocache=' + Math.random() * 10;"));
    client.println(F("var request = new XMLHttpRequest();"));
    client.println(F("var status, errors, SPIsendParametersStatus;"));
    client.println(F("request.onreadystatechange = function () {"));
    client.println(F("if (this.readyState == 4 &&"));
    client.println(F("this.status == 200 &&"));
    client.println(F("this.responseText != null) {"));
    client.println(F("statusArray = this.responseText.split('&');"));
    client.println(F("workingMode = parseInt(statusArray[0].split('=')[1]);"));
    client.println(F("(workingMode) ? document.getElementById('working_mode_text').innerHTML = '<p>Encoder Mode</p>' : document.getElementById('working_mode_text').innerHTML = '<p>Idle Mode</p>';"));
    client.println(F("errors = parseInt(statusArray[1].split('=')[1]);"));
    client.println(F("((errors >> 7) & 0x01) ? document.getElementById('sensLED').className = 'dot_green' : document.getElementById('sensLED').className = 'dot_red';"));
    client.println(F("((errors >> 6) & 0x01) ? document.getElementById('stmhLED').className = 'dot_green' : document.getElementById('stmhLED').className = 'dot_red';"));
    client.println(F("((errors >> 5) & 0x01) ? document.getElementById('spiLED').className = 'dot_green' : document.getElementById('spiLED').className = 'dot_red';"));
    client.println(F("((errors >> 3) & 0x01) ? document.getElementById('pwrLED').className = 'dot_green' : document.getElementById('pwrLED').className = 'dot_red';"));
    client.println(F("((errors >> 2) & 0x01) ? document.getElementById('tempLED').className = 'dot_green' : document.getElementById('tempLED').className = 'dot_red';"));
    client.println(F("((errors >> 1) & 0x01) ? document.getElementById('stmsLED').className = 'dot_green' : document.getElementById('stmsLED').className = 'dot_red';"));
    client.println(F("document.getElementById('tempValue').innerHTML = \"Temperature: \" + statusArray[3].split('=')[1] "));
    client.println(F("document.getElementById('humValue').innerHTML = \"Humidity: \" + statusArray[4].split('=')[1] "));
    client.println(F("document.getElementById('axisX').innerHTML = \"X-Axis: \" + statusArray[5].split('=')[1] "));
    client.println(F("document.getElementById('axisY').innerHTML = \"Y-Axis: \" + statusArray[6].split('=')[1] "));
    client.println(F("document.getElementById('barPressure').innerHTML = \"Pressure: \" + statusArray[7].split('=')[1] "));
    client.println(F("SPIsendParametersStatus = parseInt(statusArray[2].split('=')[1]);"));
    client.println(F("if (SPIsendParametersStatus == 0 && flagAlert == 1) {"));
    client.println(F("alert('Parameters updated succesfully');"));
    client.println(F("flagAlert = 0;"));
    client.println(F("}"));
    client.println(F("else if (SPIsendParametersStatus > 0 && flagAlert == 1) {"));
    client.println(F("alert(' Error in SPI sending parameters. Probably the SPI bus is broken.'); flagAlert = 0;"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("request.open('GET', 'ajaxupdatediag' + nocache, true);"));
    client.println(F("request.send(null);"));
    client.println(F("}, 400);"));
    client.println(F("// function that manages the shifting between pages. It needs to request variables' values from arduino.  "));
    client.println(F("function updateForm(whichOne) {"));
    client.println(F("getValuesFromArduino();"));
    client.println(F("document.getElementById(\"pages\").innerHTML = document.getElementById(whichOne).innerHTML; "));
    client.println(F("return false;"));
    client.println(F("}"));
    client.println(F("// function that populates the equivalent encoder resolution field in the resolution page  "));
    client.println(F("function estimateResolution() {"));
    client.println(F("var rollRad = parseFloat(document.getElementById('rollRad').value);"));
    client.println(F("var leaThick = parseFloat(document.getElementById('leaThick').value);"));
    client.println(F("document.getElementById('encRes').value = (2 * Math.PI * (rollRad + leaThick) / cameraRes * 1000).toFixed(2);"));
    client.println(F("}"));
    client.println(F("// function that sends a reset request to the arduino. It refreshes the page when the server responds.  "));
    client.println(F("function ajaxSendReset() {"));
    client.println(F("if (confirm('Device will be restarted. Are you sure?')) {"));
    client.println(F("console.log('Reset Requested');"));
    client.println(F("nocache = '&nocache=' + Math.random() * 10;"));
    client.println(F("var request = new XMLHttpRequest();"));
    client.println(F("request.onreadystatechange = function () {"));
    client.println(F("if (this.readyState == 4) {"));
    client.println(F("if (this.status == 200) {"));
    client.println(F("if (this.responseText != null) {"));
    client.println(F("refreshPage();"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("request.open('GET', 'ajaxreset' + nocache, true);"));
    client.println(F("request.send(null);"));
    client.println(F("}"));
    client.println(F("}"));
    client.println(F("// Header end"));
    client.println(F("</script>"));
}

void ServerEncoder::serverBody(EthernetClient client)
{
    client.println(F("<!-- Body -->"));
    client.println(F("<body onload='loadPage()'>"));
    client.println(F("<div id='grid-page'>"));
    client.println(F("<header id='header'>"));
    client.println(F("<div class='innertube'>"));
    client.println(F("<a href=''>"));
    // * SVG begin
    ServerEncoder::serverSVG(client);
    // * SVG end
    client.println(F("</a>"));
    client.println(F("<!--<h1>Brevetti CEA</h1> -->"));
    client.println(F("<h1>BESTduino encoder</h1>"));
    client.println(F("</div>"));
    client.println(F("</header>"));
    client.println(F("<!--<div id='wrapper'>-->"));
    client.println(F("<!-- Navigation side bar -->"));
    client.println(F("<nav id='nav'>"));
    client.println(F("<div class='innertube'>"));
    client.println(F("<h2 style='text-align: center;'>Menu</h2>"));
    client.println(F("<br>"));
    client.println(F("<ul>"));
    client.println(F("<li><a id='statusLink' title='Click to show device status' href='#'"));
    client.println(F("onclick='updateForm(\"deviceStatus\");'>Encoder status</a>"));
    client.println(F("</li>"));
    client.println(F("<br>"));
    client.println(F("<li><a id='netParamLink' title='Click to show network parameters' href='#'"));
    client.println(F("onclick='updateForm(\"networkParams\");'>Network parameters</a>"));
    client.println(F("</li>"));
    client.println(F("<br>"));
    client.println(F("<li><a id='encParamLink' title='Click to show sensor parameters' href='#'"));
    client.println(F("onclick='updateForm(\"encoderParams\");'>Encoder parameters</a>"));
    client.println(F("</li>"));
    client.println(F("<br>"));
    client.println(F("<li><a id='resEstimationLink' title='Click to show resolution estimation page' href='#'"));
    client.println(F("onclick='updateForm(\"resEstimation\");'>Estimated resolution</a>"));
    client.println(F("</li>"));
    client.println(F("<br>"));
    client.println(F("<li><a id='resOeirnetationLink' title='Click to show oriantation page' href='#'"));
    client.println(F("onclick='updateForm(\"resOrientation\");'>Encoder positioning</a>"));
    client.println(F("</li>"));
    client.println(F("</ul>"));
    client.println(F("</div>"));
    client.println(F("</nav>"));
    client.println(F("<!-- Main content -->"));
    client.println(F("<main id='content'>"));
    client.println(F("<div class='innertube'>"));
    client.println(F("<div id='pages'>"));
    client.println(F("</div>"));
    client.println(F("</div>"));
    client.println(F("</main>"));
    client.println(F("</div>"));
    client.println(F("<div id='deviceStatus' style='display: none;'>"));
    client.println(F("<div id='grid_container_statuspage'>"));
    client.println(F("<div id='working_mode'>"));
    client.println(F("<h2>Working Mode</h2>"));
    client.println(F("<div id='working_mode_text'></div>"));
    client.println(F("</div>"));
    client.println(F("<div id='grid_container_sensors'>"));
    client.println(F("<h2 style='grid-column:1 / span 3;'>Ambient sensors</h2>"));
    client.println(F("<p id='tempValue'>Internal temperature</p>"));
    client.println(F("<p id='humValue'>Relative humidity</p>"));
    client.println(F("<p id='barPressure'>Barometric pressure</p>"));
    client.println(F("</div>"));
    client.println(F("<div id='grid_container_status'>"));
    client.println(F("<h2 style='grid-column:1 / span 6;'>Errors</h2>"));
    client.println(F("<div>Main sensor</div>"));
    client.println(F("<div>STM Hardware</div>"));
    client.println(F("<div>SPI Communication</div>"));
    client.println(F("<div>Power Supply</div>"));
    client.println(F("<div>Overheating</div>"));
    client.println(F("<div>STM Software Time</div>"));
    client.println(F("<div><span id='sensLED' class='dot_red'></span></div>"));
    client.println(F("<div><span id='stmhLED' class='dot_red'></span></div>"));
    client.println(F("<div><span id='spiLED' class='dot_red'></span></div>"));
    client.println(F("<div><span id='pwrLED' class='dot_red'></span></div>"));
    client.println(F("<div><span id='tempLED' class='dot_red'></span></div>"));
    client.println(F("<div><span id='stmsLED' class='dot_red'></span></div>"));
    client.println(F("</div>"));
    client.println(F("<div style='display:grid; justify-content: center;'>"));
    client.println(F("<input type='button' onclick='ajaxSendReset()' value='Restart Device'>"));
    client.println(F("</div>"));
    client.println(F("</div>"));
    client.println(F("</div>"));
    client.println(F("<!-- Forms (initially hidden, shown via javascript) -->"));
    client.println(F("<!-- Form for network parameters -->"));
    client.println(F("<div id='networkParams' style='display: none;'>"));
    client.println(F("<form method='get' onsubmit='return ajaxGet(\"network\")'>"));
    client.println(F("<table class='formdata' summary='This table contains a form for saving network parameters'>"));
    client.println(F("<caption>Network Parameters</caption>"));
    client.println(F("<colgroup>"));
    client.println(F("<col class='codecol'>"));
    client.println(F("<col class='namecol'>"));
    client.println(F("<col class='valuecol'>"));
    client.println(F("<col class='rwcol'>"));
    client.println(F("<col class='mincol'>"));
    client.println(F("<col class='maxcol'>"));
    client.println(F("<col class='desccol'>"));
    client.println(F("</colgroup>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='col'>Code</th>"));
    client.println(F("<th scope='col'>Name</th>"));
    client.println(F("<th scope='col'>Value</th>"));
    client.println(F("<th scope='col'>R/W</th>"));
    client.println(F("<th scope='col'>Min</th>"));
    client.println(F("<th scope='col'>Max</th>"));
    client.println(F("<th scope='col'>Description</th>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p01</th>"));
    client.println(F("<td style='text-align: left;'>Device Index</td>"));
    client.println(F("<td><input type=' number' oninput='parseDeviceID()' name='deviceID' id='deviceID' min='1' max='235'"));
    client.println(F("required></td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>1</td>"));
    client.println(F("<td>235</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Progressive index of the device. Make sure that each "));
    client.println(F("device in a net has a<br>"));
    client.println(F("univoque ID. This parameter directly sets the IP Address of the device and<br>the remote port to"));
    client.println(F("which it sends UDP data</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p02[0]</th>"));
    client.println(F("<td rowspan='4' style='text-align: left;'>IP Address</td>"));
    client.println(F("<td><input type='text' name='addressIP[0]' id='addressIP[0]' size='3' readonly></td>"));
    client.println(F("<td rowspan='4'>R</td>"));
    client.println(F("<td rowspan='4'></td>"));
    client.println(F("<td rowspan='4'></td>"));
    client.println(F("<td class='description' rowspan='4' style='text-align: left;'>IP Address for the ethernet interface of "));
    client.println(F("the device; p02[0] to"));
    client.println(F("p02[2] are fixed<br> while P02[3] is computed as: 20 + p01</td>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p02[1]</th>"));
    client.println(F("<td><input type='text' name='addressIP[1]' id='addressIP[1]' size='3' readonly></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p02[2]</th>"));
    client.println(F("<td><input type='text' name='addressIP[2]' id='addressIP[2]' size='3' readonly></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p02[3]</th>"));
    client.println(F("<td><input type='text' name='addressIP[3]' id='addressIP[3]' size='3' readonly></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p03[0]</th>"));
    client.println(F("<td rowspan='6' style='text-align: left;'>MAC Address</td>"));
    client.println(F("<td><input type='text' title='Insert an hexadecimal value (2 characters from 0 to F)'"));
    client.println(F("id='addressMAC[0]' name='addressMAC[0]' pattern='[0-9a-fA-F]{2}' size='2' required></td>"));
    client.println(F("<td rowspan='6'>RW</td>"));
    client.println(F("<td rowspan='6'>00</td>"));
    client.println(F("<td rowspan='6'>FF</td>"));
    client.println(F("<td class='description' rowspan='6' style='text-align: left;'>MAC Address for the ethernet"));
    client.println(F("interface of the device. When there is more<br> than one device are present in the same subnet, "));
    client.println(F("make sure that each one<br> has a unique MAC address</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p03[1]</th>"));
    client.println(F("<td><input type='text' title='Insert an hexadecimal value (2 characters from 0 to F).'"));
    client.println(F("id='addressMAC[1]' name='addressMAC[1]' pattern='[0-9a-fA-F]{2}' size='2' required></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p03[2]</th>"));
    client.println(F("<td><input type='text' title='Insert an hexadecimal value (2 characters from 0 to F).'"));
    client.println(F("id='addressMAC[2]' name='addressMAC[2]' pattern='[0-9a-fA-F]{2}' size='2' required></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p03[3]</th>"));
    client.println(F("<td><input type='text' title='Insert an hexadecimal value (2 characters from 0 to F).'"));
    client.println(F("id='addressMAC[3]' name='addressMAC[3]' pattern='[0-9a-fA-F]{2}' size='2' required></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p03[4]</th>"));
    client.println(F("<td><input type='text' title='Insert an hexadecimal value (2 characters from 0 to F).'"));
    client.println(F("id='addressMAC[4]' name='addressMAC[4]' pattern='[0-9a-fA-F]{2}' size='2' required></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p03[5]</th>"));
    client.println(F("<td><input type='text' title='Insert an hexadecimal value (2 characters from 0 to F).'"));
    client.println(F("id='addressMAC[5]' name='addressMAC[5]' pattern='[0-9a-fA-F]{2}' size='2' required></td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p04</th>"));
    client.println(F("<td style='text-align: left;'>Local UDP Port</td>"));
    client.println(F("<td><input type=' number' name='localPort' id='localPort' min='3000' max='4000' required></td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>3000</td>"));
    client.println(F("<td>4000</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Local port that receives UDP data.</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p05</th>"));
    client.println(F("<td style='text-align: left;'>Remote UDP Port</td>"));
    client.println(F("<td><input type=' number' id='remotePort' name='remotePort' readonly></td>"));
    client.println(F("<td>R</td>"));
    client.println(F("<td></td>"));
    client.println(F("<td></td>"));
    client.println(F("<td class='description' style='text-align: left;'>Remote port to which the device sends UDP data."));
    client.println(F("It is computed as: 3000<br> + p01</td>"));
    client.println(F("</tr>"));
    client.println(F("</table>"));
    client.println(F("<!-- Buttons -->"));
    client.println(F("<div class='buttons'>"));
    client.println(F("<input type='reset' name='resetNetworkParams'>"));
    client.println(F("<input type='submit' name='submitNetworkParams' onclick='clicked(event)'>"));
    client.println(F("</div>"));
    client.println(F("</form>"));
    client.println(F("</div>"));
    client.println(F("<!-- Form for encoder parameters -->"));
    client.println(F("<div id='encoderParams' style='display: none;'>"));
    client.println(F("<form method='get' onsubmit='return ajaxGet(\"encoder\")'>"));
    client.println(F("<table class='formdata' summary='This table contains a form for saving encoder parameters'>"));
    client.println(F("<caption>Encoder parameters</caption>"));
    client.println(F("<colgroup>"));
    client.println(F("<col class='codecol'>"));
    client.println(F("<col class='namecol2'>"));
    client.println(F("<col class='valuecol2'>"));
    client.println(F("<col class='unitcol'>"));
    client.println(F("<col class='rwcol'>"));
    client.println(F("<col class='mincol'>"));
    client.println(F("<col class='maxcol'>"));
    client.println(F("<col class='desccol'>"));
    client.println(F("</colgroup>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='col'>Code</th>"));
    client.println(F("<th scope='col'>Name</th>"));
    client.println(F("<th scope='col'>Value</th>"));
    client.println(F("<th scope='col'>Unit</th>"));
    client.println(F("<th scope='col'>R/W</th>"));
    client.println(F("<th scope='col'>Min</th>"));
    client.println(F("<th scope='col'>Max</th>"));
    client.println(F("<th scope='col'>Description</th>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p21</th>"));
    client.println(F("<td style='text-align: left;'>Measuring distance</td>"));
    client.println(F("<td><input type='number' name='encDist' id='encDist' min='15' max='35'></td>"));
    client.println(F("<td>mm</td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>15</td>"));
    client.println(F("<td>35</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Distance between the reading face of the sensor and the tracked"));
    client.println(F("<br>surface</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p22</th>"));
    client.println(F("<td style='text-align: left;'>Tracking resolution</td>"));
    client.println(F("<td><input type='number' name='camRes' id='camRes' min='30' max='50'></td>"));
    client.println(F("<td>um</td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>30</td>"));
    client.println(F("<td>50</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Minimun tracking resolution of the inspection system</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p23</th>"));
    client.println(F("<td style='text-align: left;'>Sensor resolution</td>"));
    client.println(F("<td><input type='number' name='patRes' id='patRes' min='1000' max='4000'></td>"));
    client.println(F("<td>cpi</td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>1000</td>"));
    client.println(F("<td>4000</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Counts per inch of the main sensor</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p24</th>"));
    client.println(F("<td style='text-align: left;'>Encoder input filter</td>"));
    client.println(F("<td><input type='number' name='inFilter' id='inFilter' min='5' max='40'></td>"));
    client.println(F("<td>samples</td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>5</td>"));
    client.println(F("<td>40</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Number of samples composing the window of the moving"));
    client.println(F("average<br> filter applied to the measure of the main sensor</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p25</th>"));
    client.println(F("<td style='text-align: left;'>Encoder output filter</td>"));
    client.println(F("<td><input type='number' name='outFilter' id='outFilter' min='2' max='40'></td>"));
    client.println(F("<td>samples</td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>2</td>"));
    client.println(F("<td>40</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Number of samples composing the window of the moving"));
    client.println(F("average<br> filter applied to the output frequency signal</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p26</th>"));
    client.println(F("<td style='text-align: left;'>Sampling Period</td>"));
    client.println(F("<td><input type='number' name='tSample' id='tSample' min='350' max='1300'></td>"));
    client.println(F("<td>us</td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>350</td>"));
    client.println(F("<td>1300</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Time between consecutive samples of the main sensor"));
    client.println(F("measure</td>"));
    client.println(F("</tr>"));
    client.println(F("<tr>"));
    client.println(F("<th scope='row'>p27</th>"));
    client.println(F("<td style='text-align: left;'>Main Sensor Current</td>"));
    client.println(F("<td><select class='input' name='patCurr' id='patCurr'>"));
    client.println(F("<option value='5'>0x05 (6.0mA)</option>"));
    client.println(F("<option value='6'>0x06 (7.2mA)</option>"));
    client.println(F("</select></td>"));
    client.println(F("<td>mA</td>"));
    client.println(F("<td>RW</td>"));
    client.println(F("<td>0x05</td>"));
    client.println(F("<td>0x06</td>"));
    client.println(F("<td class='description' style='text-align: left;'>Maximun current for main sensor</td>"));
    client.println(F("</tr>"));
    client.println(F("</table>"));
    client.println(F("<!-- Buttons -->"));
    client.println(F("<div class='buttons'>"));
    client.println(F("<input type='reset' name='resetEncoderParams'>"));
    client.println(F("<input type='submit' name='submitEncoderParams'>"));
    client.println(F("</div>"));
    client.println(F("</div>"));
    client.println(F("</form>"));
    client.println(F("</div>"));
    client.println(F("<!-- Form for encoder resolution estimation -->"));
    client.println(F("<div id='resEstimation' style='display:none'>"));
    client.println(F("<form>"));
    client.println(F("<!-- Roller radius -->"));
    client.println(F("<div>"));
    client.println(F("<label for='rollRad'>Roller radius:</label><br>"));
    client.println(F("<input type='number' name='rollRad' id='rollRad' oninput='estimateResolution()' min='0'> mm"));
    client.println(F("</div>"));
    client.println(F("<!-- Leather thickness -->"));
    client.println(F("<div>"));
    client.println(F("<label for='leaThick'>Leather thickness:</label><br>"));
    client.println(F("<input type='number' name='leaThick' id='leaThick' oninput='estimateResolution()' min='0'> mm"));
    client.println(F("</div>"));
    client.println(F("<!-- Encoder resolution -->"));
    client.println(F("<div>"));
    client.println(F("<label for='encRes'>Equivalent Rotary Encoder Resolution:</label><br>"));
    client.println(F("<input type='number' name='encRes' id='encRes' readonly> ppr"));
    client.println(F("</div>"));
    client.println(F("</form>"));
    client.println(F("</div>"));
    client.println(F("</form>"));
    client.println(F("</div>"));
    client.println(F("<!-- Form for encoder orientation Panel -->"));
    client.println(F("<div id='resOrientation' style='display:none'>"));
    client.println(F("<div>    "));
    client.println(F("<h2 style='grid-column:1 / span 2;'>Sensors</h2> "));
    client.println(F("<p id='axisX'> Axis X</p> "));
    client.println(F("<p id='axisY'>Axis Y</p> "));
    client.println(F("</div> "));
    client.println(F("</div>"));
    client.println(F("</body>"));
    client.println(F("</html>"));
}

void ServerEncoder::serverSVG(EthernetClient client)
{
    client.println(F("<svg"));
    client.println(F("version='1.1'"));
    client.println(F("width='250'"));
    client.println(F("height='100'"));
    client.println(F("viewBox='0 0 106.92 40.451'"));
    client.println(F("xmlns='http://www.w3.org/2000/svg'"));
    client.println(F(">"));
    client.println(F("<g transform='translate(-55.938 -128.06)'>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.9941 .10843 -.042681 .99909 0 0)'"));
    client.println(F("d='m 88.242604,124.87472 a 5.7075477,2.966697 0 0 1 -5.709377,2.96566 5.7075477,2.966697 0 0 1 -5.705717,-2.96756 5.7075477,2.966697 0 0 1 5.709023,-2.96584 5.7075477,2.966697 0 0 1 5.706072,2.96737 l -5.707548,-6.7e-4 z'"));
    client.println(F("style='fill: #1a6ca5; stroke-width: 0.17323'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.99329 .11563 -.10367 .99461 0 0)'"));
    client.println(F("d='m 88.032317,129.48342 a 6.468101,3.3124299 0 0 1 -6.470175,3.31126 6.468101,3.3124299 0 0 1 -6.466026,-3.31339 6.468101,3.3124299 0 0 1 6.469773,-3.31147 6.468101,3.3124299 0 0 1 6.466428,3.31319 l -6.4681,-7.6e-4 z'"));
    client.println(F("style='fill: #005b9a; stroke-width: 0.19486'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.99782 .065989 -.032543 .99947 0 0)'"));
    client.println(F("d='m 114.79591,123.95309 a 3.7364023,2.0366292 0 0 1 -3.7376,2.03592 3.7364023,2.0366292 0 0 1 -3.7352,-2.03722 3.7364023,2.0366292 0 0 1 3.73737,-2.03604 3.7364023,2.0366292 0 0 1 3.73543,2.03709 l -3.7364,-4.6e-4 z'"));
    client.println(F("style='fill: #669dc3; stroke-width: 0.11613'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.99706 .076651 .038593 .99926 0 0)'"));
    client.println(F("d='m 97.394056,123.567 a 4.2802863,2.3383965 0 0 1 -4.281659,2.33757 4.2802863,2.3383965 0 0 1 -4.278914,-2.33907 4.2802863,2.3383965 0 0 1 4.281393,-2.33772 4.2802863,2.3383965 0 0 1 4.27918,2.33893 l -4.280286,-5.3e-4 z'"));
    client.println(F("style='fill: #4c8cb9; stroke-width: 0.13319'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.99698 .077711 -.061541 .9981 0 0)'"));
    client.println(F("d='m 89.469049,155.44257 a 4.2497115,2.0535545 0 0 1 -4.251074,2.05283 4.2497115,2.0535545 0 0 1 -4.248349,-2.05415 4.2497115,2.0535545 0 0 1 4.25081,-2.05296 4.2497115,2.0535545 0 0 1 4.248613,2.05403 l -4.249712,-4.7e-4 z'"));
    client.println(F("style='fill: #669dc3; stroke-width: 0.12437'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.99834 .057657 .042861 .99908 0 0)'"));
    client.println(F("d='m 87.128543,126.95689 a 5.1153517,2.947073 0 0 1 -5.116992,2.94603 5.1153517,2.947073 0 0 1 -5.113711,-2.94792 5.1153517,2.947073 0 0 1 5.116674,-2.94622 5.1153517,2.947073 0 0 1 5.114029,2.94774 l -5.115352,-6.7e-4 z'"));
    client.println(F("style='fill: #327cae; stroke-width: 0.16346'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.98952 .14442 -.15601 .98776 0 0)'"));
    client.println(F("d='m 137.15442,114.69415 a 3.2675521,1.8189948 0 0 1 -3.2686,1.81836 3.2675521,1.8189948 0 0 1 -3.2665,-1.81952 3.2675521,1.8189948 0 0 1 3.2684,-1.81847 3.2675521,1.8189948 0 0 1 3.2667,1.81941 l -3.26755,-4.2e-4 z'"));
    client.println(F("style='fill: #7eadcc; stroke-width: 0.10264'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.99581 .091458 0 1 0 0)'"));
    client.println(F("d='m 69.799513,146.03839 a 5.8066964,2.8262386 0 0 1 -5.808558,2.82525 5.8066964,2.8262386 0 0 1 -5.804834,-2.82706 5.8066964,2.8262386 0 0 1 5.808197,-2.82542 5.8066964,2.8262386 0 0 1 5.805195,2.82688 l -5.806696,-6.4e-4 z'"));
    client.println(F("style='fill: #327cae; stroke-width: 0.17054'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("d='m 133.92534,139.8692 a 1.5469486,0.849783 0 0 1 -1.54745,0.84948 1.5469486,0.849783 0 0 1 -1.54645,-0.85003 1.5469486,0.849783 0 0 1 1.54735,-0.84954 1.5469486,0.849783 0 0 1 1.54655,0.84998 l -1.54695,-1.9e-4 z'"));
    client.println(F("style='fill: #dbe8f0; stroke-width: 0.048268'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.9993 .037496 -.031902 .99949 0 0)'"));
    client.println(F("d='m 128.04653,129.67315 a 2.7713108,1.4593593 0 0 1 -2.7722,1.45885 2.7713108,1.4593593 0 0 1 -2.77042,-1.45978 2.7713108,1.4593593 0 0 1 2.77203,-1.45894 2.7713108,1.4593593 0 0 1 2.77059,1.45969 l -2.77131,-3.3e-4 z'"));
    client.println(F("style='fill: #9bbfd7; stroke-width: 0.084663'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.99787 .065236 -.058828 .99827 0 0)'"));
    client.println(F("d='m 136.1497,127.70911 a 2.4187694,1.3248428 0 0 1 -2.41955,1.32437 2.4187694,1.3248428 0 0 1 -2.41799,-1.32522 2.4187694,1.3248428 0 0 1 2.41939,-1.32446 2.4187694,1.3248428 0 0 1 2.41815,1.32514 l -2.41877,-3e-4 z'"));
    client.println(F("style='fill: #cedfec; stroke-width: 0.075361'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.99655 .083044 -.095342 .99544 0 0)'"));
    client.println(F("d='m 88.233906,151.34466 a 4.8422136,2.18296 0 0 1 -4.843766,2.18219 4.8422136,2.18296 0 0 1 -4.84066,-2.18359 4.8422136,2.18296 0 0 1 4.843465,-2.18233 4.8422136,2.18296 0 0 1 4.840962,2.18345 l -4.842214,-4.9e-4 z'"));
    client.println(F("style='fill: #4c8cb9; stroke-width: 0.13687'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.99198 .12641 -.10504 .99447 0 0)'"));
    client.println(F("d='m 109.02447,153.50688 a 2.7919016,1.4252024 0 0 1 -2.7928,1.4247 2.7919016,1.4252024 0 0 1 -2.791,-1.42561 2.7919016,1.4252024 0 0 1 2.79262,-1.42479 2.7919016,1.4252024 0 0 1 2.79118,1.42552 l -2.7919,-3.2e-4 z'"));
    client.println(F("style='fill: #9abed7; stroke-width: 0.083976'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.99394 .10992 -.10876 .99407 0 0)'"));
    client.println(F("d='m 115.7891,155.30369 a 2.649297,1.2408659 0 0 1 -2.65015,1.24043 2.649297,1.2408659 0 0 1 -2.64845,-1.24123 2.649297,1.2408659 0 0 1 2.64999,-1.2405 2.649297,1.2408659 0 0 1 2.64861,1.24115 l -2.6493,-2.9e-4 z'"));
    client.println(F("style='fill: #b4cfe1; stroke-width: 0.07633'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.98163 .19081 -.19219 .98136 0 0)'"));
    client.println(F("d='m 116.26021,145.75712 a 3.4139752,1.7629119 0 0 1 -3.41507,1.76229 3.4139752,1.7629119 0 0 1 -3.41288,-1.76342 3.4139752,1.7629119 0 0 1 3.41486,-1.7624 3.4139752,1.7629119 0 0 1 3.41309,1.76331 l -3.41397,-4e-4 z'"));
    client.println(F("style='fill: #7fadcc; stroke-width: 0.10328'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.99892 .046409 -.061256 .99812 0 0)'"));
    client.println(F("d='m 144.39349,135.04374 a 1.2967063,0.71058506 0 0 1 -1.29712,0.71033 1.2967063,0.71058506 0 0 1 -1.29629,-0.71079 1.2967063,0.71058506 0 0 1 1.29704,-0.71038 1.2967063,0.71058506 0 0 1 1.29637,0.71075 l -1.2967,-1.6e-4 z'"));
    client.println(F("style='fill: #dbe8f0; stroke-width: 0.040411'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("d='m 131.73408,138.14221 a 2.0338805,1.0376607 0 0 1 -2.03454,1.0373 2.0338805,1.0376607 0 0 1 -2.03323,-1.03796 2.0338805,1.0376607 0 0 1 2.03441,-1.03736 2.0338805,1.0376607 0 0 1 2.03336,1.03789 l -2.03388,-2.3e-4 z'"));
    client.println(F("style='fill: #dbe8f0; stroke-width: 0.061159'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.99732 .073137 -.070802 .99749 0 0)'"));
    client.println(F("d='m 114.87647,159.5899 a 2.284729,1.0818189 0 0 1 -2.28546,1.08144 2.284729,1.0818189 0 0 1 -2.284,-1.08213 2.284729,1.0818189 0 0 1 2.28532,-1.08151 2.284729,1.0818189 0 0 1 2.28414,1.08207 l -2.28473,-2.5e-4 z'"));
    client.println(F("style='fill: #bcd4e6; stroke-width: 0.066186'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.98977 .14265 -.11761 .99306 0 0)'"));
    client.println(F("d='m 86.171149,134.8703 a 6.8088064,3.2872441 0 0 1 -6.81099,3.28608 6.8088064,3.2872441 0 0 1 -6.806622,-3.28819 6.8088064,3.2872441 0 0 1 6.810566,-3.28629 6.8088064,3.2872441 0 0 1 6.807046,3.28799 l -6.808806,-7.5e-4 z'"));
    client.println(F("style='fill: #1a6ca5; stroke-width: 0.19917'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("d='m 114.15754,166.992 a 1.2180758,0.64532769 0 0 1 -1.21846,0.6451 1.2180758,0.64532769 0 0 1 -1.21769,-0.64551 1.2180758,0.64532769 0 0 1 1.21839,-0.64514 1.2180758,0.64532769 0 0 1 1.21776,0.64547 l -1.21807,-1.4e-4 z'"));
    client.println(F("style='fill: #d8e6f0; stroke-width: 0.037325'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("transform='matrix(.99575 .092054 -.092743 .99569 0 0)'"));
    client.println(F("d='m 122.94398,157.00644 a 2.0591724,0.92469257 0 0 1 -2.05983,0.92437 2.0591724,0.92469257 0 0 1 -2.05851,-0.92496 2.0591724,0.92469257 0 0 1 2.0597,-0.92442 2.0591724,0.92469257 0 0 1 2.05864,0.9249 l -2.05917,-2.1e-4 z'"));
    client.println(F("style='fill: #cfe0ec; stroke-width: 0.058092'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("d='m 111.4212,167.35117 a 1.451732,0.83200169 0 0 1 -1.4522,0.83171 1.451732,0.83200169 0 0 1 -1.45126,-0.83225 1.451732,0.83200169 0 0 1 1.4521,-0.83176 1.451732,0.83200169 0 0 1 1.45136,0.8322 l -1.45173,-1.9e-4 z'"));
    client.println(F("style='fill: #d8e6f0; stroke-width: 0.046267'"));
    client.println(F("/>"));
    client.println(F("<path"));
    client.println(F("d='m 116.28399,166.36367 a 1.0311508,0.50566018 0 0 1 -1.03148,0.50549 1.0311508,0.50566018 0 0 1 -1.03082,-0.50581 1.0311508,0.50566018 0 0 1 1.03141,-0.50552 1.0311508,0.50566018 0 0 1 1.03089,0.50578 l -1.03115,-1.2e-4 z'"));
    client.println(F("style='fill: #d8e6f0; stroke-width: 0.030399'"));
    client.println(F("/>"));
    client.println(F("<text"));
    client.println(F("transform='matrix(.91842 0 0 .93117 13.809 17.958)'"));
    client.println(F("x='75.40625'"));
    client.println(F("y='147.43906'"));
    client.println(F("style='"));
    client.println(F("fill: #005c9b;"));
    client.println(F("font-family: 'Source Sans Pro';"));
    client.println(F("font-size: 10.583px;"));
    client.println(F("inline-size: 90.0916;"));
    client.println(F("line-height: 1.25;"));
    client.println(F("stroke-width: 0.26458;"));
    client.println(F("white-space: pre;"));
    client.println(F("'"));
    client.println(F("xml:space='preserve'"));
    client.println(F(">"));
    client.println(F("<tspan"));
    client.println(F("x='70'"));
    client.println(F("y='146'"));
    client.println(F("style='"));
    client.println(F("fill: #005c9b;"));
    client.println(F("font-family: 'Sero Pro';"));
    client.println(F("font-size: 13.5px;"));
    client.println(F("stroke-width: 0.26458;"));
    client.println(F("'"));
    client.println(F(">"));
    client.println(F("brevetti cea"));
    client.println(F("</tspan>"));
    client.println(F("</text>"));
    client.println(F("<text"));
    client.println(F("transform='matrix(.99913 0 0 .99537 .048939 .7794)'"));
    client.println(F("style='"));
    client.println(F("fill: #000000;"));
    client.println(F("font-family: 'Franklin Gothic Medium Cond';"));
    client.println(F("font-size: 10.583px;"));
    client.println(F("line-height: 1.8;"));
    client.println(F("white-space: pre;"));
    client.println(F("'"));
    client.println(F("xml:space='preserve'"));
    client.println(F("/>"));
    client.println(F("<text"));
    client.println(F("transform='scale(1.2151 .82295)'"));
    client.println(F("x='30'"));
    client.println(F("y='196'"));
    client.println(F("style='"));
    client.println(F("fill: #2c6790;"));
    client.println(F("font-family: 'Source Code Pro';"));
    client.println(F("font-size: 3px;"));
    client.println(F("line-height: 1.8;"));
    client.println(F("stroke-width: 0.56;"));
    client.println(F("'"));
    client.println(F("xml:space='preserve'"));
    client.println(F(">"));
    client.println(F("<tspan"));
    client.println(F("x='66.9'"));
    client.println(F("y='193'"));
    client.println(F("style='"));
    client.println(F("fill: #4c87b1;"));
    client.println(F("font-family: DDTW00-Book;"));
    client.println(F("font-size: 5px;"));
    client.println(F("stroke-width: 0.56;"));
    client.println(F("line-height: 1.8;"));
    client.println(F("'"));
    client.println(F(">"));
    client.println(F("INSPECTION MACHINES"));
    client.println(F("</tspan>"));
    client.println(F("</text>"));
    client.println(F("</g>"));
    client.println(F("</svg>"));
}

unsigned char ServerEncoder::h2d(unsigned char hex_1, unsigned char hex_2)
{
    /*
        This function takes two characters and outputs a char that meets the formatting of a byte in HEX
    */

    unsigned char temp1, temp2;

    if (hex_1 > 0x39)
        hex_1 -= 7; // adjust for hex letters upper or lower case
    temp1 = hex_1 & 0xf;

    if (hex_2 > 0x39)
        hex_2 -= 7; // adjust for hex letters upper or lower case
    temp2 = hex_2 & 0xf;

    return ((temp1 << 4) | temp2);
}

String ServerEncoder::findData(int16_t from)
{
    /*
        This function returns a substring of the HTTP request "webGetString" that is contained between a
        '&' and a '=', starting from the index "from"
    */

    boolean finish = false;
    boolean reading = false;
    int16_t i = from;
    String parsedData;

    while (!finish)
    {
        if ((webGetString[i] == '&') || (webGetString[i] == ' '))
        {
            finish = true;
            return parsedData;
        }
        if (reading)
        {
            parsedData += webGetString[i];
            DEBUG_SERVERLN(parsedData);
        }
        if (webGetString[i] == '=')
        {
            reading = true;
        }
        i++;
    }
}

uint8_t ServerEncoder::parseResponse(void)
{
    /*
        This function extracts from the HTTP request of the client (submit method='GET') all the relevant
        parameters and stores them in the EEPROM. If some network parameters have been changed, the function
        returns 'true', otherwise it returns 'false'
    */

    bool restartNeeded = false;
    bool transmissionNeeded = false;
    int16_t tempIndex;
    String tempData;

    tempIndex = webGetString.indexOf("deviceID");
    if (tempIndex >= 0)
    {
        tempData = ServerEncoder::findData(tempIndex);
        if (tempData.toInt() != eP->deviceIndex)
        {
            eP->deviceIndex = tempData.toInt();
            DEBUG_SERVER(F("New Device ID is: "));
            DEBUG_SERVERLN(eP->deviceIndex);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = mySystem.writeReadBI2C(locationDevIndex, eP->deviceIndex); // save parameters on EEPROM
            delayMicroseconds(delayI2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("devIndex not saved"));
            else
                DEBUG_SERVERLN(F("devIndex saved on EEPROM"));
#endif
            restartNeeded = true; // indicate that encoder restart is needed
        }
    }

    tempIndex = webGetString.indexOf("addressMAC % 5B0 % 5D");
    if (tempIndex >= 0)
    {
        tempData = ServerEncoder::findData(tempIndex);
        if (ServerEncoder::h2d(tempData[0], tempData[1]) != eP->mac[0])
        {
            eP->mac[0] = ServerEncoder::h2d(tempData[0], tempData[1]);
            DEBUG_SERVER(F("New Mac Address [0] is: "));
            DEBUG_SERVERLN(eP->mac[0]);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = mySystem.writeReadBI2C(locationMacZero, eP->mac[0]);
            delayMicroseconds(delayI2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("mac[0] not saved"));
            else
                DEBUG_SERVERLN(F("mac[0] saved on EEPROM"));
#endif
            restartNeeded = true;
        }
    }

    tempIndex = webGetString.indexOf("addressMAC % 5B1 % 5D");
    if (tempIndex >= 0)
    {
        tempData = ServerEncoder::findData(tempIndex);
        if (ServerEncoder::h2d(tempData[0], tempData[1]) != eP->mac[1])
        {
            eP->mac[1] = ServerEncoder::h2d(tempData[0], tempData[1]);
            DEBUG_SERVER(F("New Mac Address [1] is: "));
            DEBUG_SERVERLN(eP->mac[1]);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = mySystem.writeReadBI2C(locationMacOne, eP->mac[1]);
            delayMicroseconds(delayI2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("mac[1] not saved"));
            else
                DEBUG_SERVERLN(F("mac[1] saved on EEPROM"));
#endif
            restartNeeded = true;
        }
    }

    tempIndex = webGetString.indexOf("addressMAC % 5B2 % 5D");
    if (tempIndex >= 0)
    {
        tempData = ServerEncoder::findData(tempIndex);
        if (ServerEncoder::h2d(tempData[0], tempData[1]) != eP->mac[2])
        {
            eP->mac[2] = ServerEncoder::h2d(tempData[0], tempData[1]);
            DEBUG_SERVER(F("New Mac Address [2] is: "));
            DEBUG_SERVERLN(eP->mac[2]);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = mySystem.writeReadBI2C(locationMacTwo, eP->mac[2]);
            delayMicroseconds(delayI2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("mac[2] not saved"));
            else
                DEBUG_SERVERLN(F("mac[2] saved on EEPROM"));
#endif
            restartNeeded = true;
        }
    }

    tempIndex = webGetString.indexOf("addressMAC % 5B3 % 5D");
    if (tempIndex >= 0)
    {
        tempData = ServerEncoder::findData(tempIndex);
        if (ServerEncoder::h2d(tempData[0], tempData[1]) != eP->mac[3])
        {
            eP->mac[3] = ServerEncoder::h2d(tempData[0], tempData[1]);
            DEBUG_SERVER(F("New Mac Address [3] is: "));
            DEBUG_SERVERLN(eP->mac[3]);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = mySystem.writeReadBI2C(locationMacThree, eP->mac[3]);
            delayMicroseconds(delayI2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("mac[3] not saved"));
            else
                DEBUG_SERVERLN(F("mac[3] saved on EEPROM"));
#endif
            restartNeeded = true;
        }
    }

    tempIndex = webGetString.indexOf("addressMAC % 5B4 % 5D");
    if (tempIndex >= 0)
    {
        tempData = ServerEncoder::findData(tempIndex);
        if (ServerEncoder::h2d(tempData[0], tempData[1]) != eP->mac[4])
        {
            eP->mac[4] = ServerEncoder::h2d(tempData[0], tempData[1]);
            DEBUG_SERVER(F("New Mac Address [4] is: "));
            DEBUG_SERVERLN(eP->mac[4]);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = mySystem.writeReadBI2C(locationMacFour, eP->mac[4]);
            delayMicroseconds(delayI2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("mac[4] not saved"));
            else
                DEBUG_SERVERLN(F("mac[4] saved on EEPROM"));
#endif
            restartNeeded = true;
        }
    }

    tempIndex = webGetString.indexOf("addressMAC % 5B5 % 5D");
    if (tempIndex >= 0)
    {
        tempData = ServerEncoder::findData(tempIndex);

        if (ServerEncoder::h2d(tempData[0], tempData[1]) != eP->mac[5])
        {
            eP->mac[5] = ServerEncoder::h2d(tempData[0], tempData[1]);
            DEBUG_SERVER(F("New Mac Address [5] is: "));
            DEBUG_SERVERLN(eP->mac[5]);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = mySystem.writeReadBI2C(locationMacFive, eP->mac[5]);
            delayMicroseconds(delayI2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("mac[5] not saved"));
            else
                DEBUG_SERVERLN(F("mac[5] saved on EEPROM"));
#endif
            restartNeeded = true;
        }
    }

    tempIndex = webGetString.indexOf("localPort");
    if (tempIndex >= 0)
    {
        tempData = ServerEncoder::findData(tempIndex);
        if (tempData.toInt() != eP->localPort)
        {
            eP->localPort = tempData.toInt();
            DEBUG_SERVER(F("New Local Port is: "));
            DEBUG_SERVERLN(eP->localPort);
#ifdef EXTMEMORY_ON
            bool tempFlag;
            tempFlag = mySystem.writeReadWI2C(locationLocalPort, eP->localPort);
            delayMicroseconds(delayI2C);
            if (!tempFlag)
                DEBUG_SERVERLN(F("localPort not saved"));
            else
                DEBUG_SERVERLN(F("localPort saved on EEPROM"));
#endif
            restartNeeded = true;
        }
    }
    for (uint8_t i = 0; i < numberParameters; i++)
    {
        tempIndex = webGetString.indexOf(deviceParamNames[i]);
        if (tempIndex >= 0)
        {
            tempData = ServerEncoder::findData(tempIndex);
            if (tempData.toInt() != eP->deviceParameters[i])
            {
                eP->deviceParameters[i] = tempData.toInt();
                DEBUG_SERVER(F("New "));
                DEBUG_SERVER(deviceParamNames[i]);
                DEBUG_SERVER(F(" is: "));
                DEBUG_SERVERLN(eP->deviceParameters[i]);
#ifdef EXTMEMORY_ON
                bool tempFlag;
                tempFlag = mySystem.writeReadWI2C(locationDevParam + 2 * i, eP->deviceParameters[i]);
                delayMicroseconds(delayI2C);
                if (!tempFlag)
                {
                    DEBUG_SERVER(deviceParamNames[i]);
                    DEBUG_SERVERLN(F(" not saved"));
                }
                else
                {
                    DEBUG_SERVER(deviceParamNames[i]);
                    DEBUG_SERVERLN(F(" saved on EEPROM"));
                }
#endif
            }
            transmissionNeeded = true;
        }
    }
    // Return 1 if only restartNeeded, 2 if only transmissionNeeded, 3 if both
    DEBUG_SERVER(F("parseResponse is returning: "));
    DEBUG_SERVERLN(restartNeeded | (transmissionNeeded << 1));
    return (restartNeeded | (transmissionNeeded << 1));
}

void ServerEncoder::ajaxInitialize(EthernetClient client)
{
    /*
        This functions is a response from the server (Arduino) to a HTTP request of the clients that contains
        the 'ajaxinitialize' string.The server sends to the client a string that contains names and values of
        the parameters. The correct format is Name1=Value1&Name2=Value2&...
    */

    client.print(F("ID ="));
    client.print(eP->deviceIndex);
    client.print(F("&"));
    client.print(F("lPort ="));
    client.print(eP->localPort);
    client.print(F("&"));
    client.print(F("macAddr ="));
    for (uint8_t i = 0; i < 6; i++)
    {
        client.print(eP->mac[i], HEX);
        if (i < 5)
            client.print(F(":"));
    }
    client.print(F("&"));
    for (uint8_t i = 0; i < numberParameters; i++)
    {
        client.print(deviceParamNames[i]);
        client.print(F("="));
        client.print(eP->deviceParameters[i]);
        if (i < numberParameters - 1)
            client.print(F("&"));
    }

#ifdef DEBUG
    DEBUG_SERVERLN(F("Response sent: "));
    DEBUG_SERVER(F("ID = "));
    DEBUG_SERVER(eP->deviceIndex);
    DEBUG_SERVER(F("&"));
    DEBUG_SERVER(F("lPort = "));
    DEBUG_SERVER(eP->localPort);
    DEBUG_SERVER(F("&"));
    DEBUG_SERVER(F("macAddr = "));
    for (uint8_t i = 0; i < 6; i++)
    {
        DEBUG_SERVERFLO(eP->mac[i], HEX);
        if (i < 5)
            DEBUG_SERVER(F(": "));
    }
    DEBUG_SERVER(F("&"));
    for (uint8_t i = 0; i < numberParameters; i++)
    {
        DEBUG_SERVER(deviceParamNames[i]);
        DEBUG_SERVER(F(" = "));
        DEBUG_SERVER(eP->deviceParameters[i]);
        if (i < numberParameters - 1)
            DEBUG_SERVER(F("&"));
    }
#endif
}

void ServerEncoder::ajaxUpdateDiag(EthernetClient client)
{
    /*
        This fcn updates the values showed in the webserver. Is a fcn called every 5 seconds.
    */
    sP->cntDebug++;
    client.print(F("working_mode = "));
    client.print(PLC_STATUS, DEC);
    client.print(F("&"));
    client.print(F("status = "));
    client.print(deviceStatus, DEC);
    client.print(F("&SPIerrorIndex = "));
    client.print(SPIerrorIndex, DEC);
    client.print(F("&tC = "));
    client.print(sP->tC, DEC);
    client.print(F("&hP = "));
    client.print(sP->hP, DEC);
#if defined(SCREEN_ON) && defined(ACCELEROMETER_ON)
    if (sP->displayScreenNum != 4)
        mySensor.imuRead();
#elif !defined(SCREEN_ON) && defined(ACCELEROMETER_ON)
    mySensor.imuRead();
#endif
    client.print(F("&axisX = "));
    client.print(iP->angX, DEC);
    client.print(F("&"));
    client.print(F("axisY = "));
    client.print(iP->angY, DEC);
    client.print(F("&bPre = "));
    client.print(sP->bPre, DEC);
    DEBUG_SERVER(F("working_mode = "));
    DEBUG_SERVERFLO(PLC_STATUS, DEC);
    DEBUG_SERVER(F("&"));
    DEBUG_SERVER(F("status = "));
    DEBUG_SERVERFLO(deviceStatus, DEC);
    DEBUG_SERVER(F("&SPIerrorIndex = "));
    DEBUG_SERVERFLO(SPIerrorIndex, DEC);
    DEBUG_SERVER(F("&"));
    DEBUG_SERVER(F("tC = "));
    DEBUG_SERVERFLO(sP->tC, DEC);
    DEBUG_SERVER(F("&hP = "));
    DEBUG_SERVERFLO(sP->hP, DEC);
}

bool ServerEncoder::displayWebServer()
{
    /*
        Function that manages the whole web server
    */

    uint8_t tempReturn = 0;
    bool restartNeeded = false;
    bool transmissionNeeded = false;

    EthernetClient client = server.available(); // Listens for new clients

    if (client)
    {
        boolean currentLineIsBlank = true;

        while (client.connected())
        { // While the client is connected and available
            if (client.available())
            {

                char c = client.read();
                if (webGetString.length() < 300)
                    webGetString += c;

                //Serial.write(c);
                if (c == '\n' && currentLineIsBlank)
                {                                       // End of a request (HTTP requests end with \n\r)
                    ServerEncoder::printHeader(client); // Sends the default response header

                    if (webGetString.indexOf("ajaxinitialize") >= 0)
                    {                                            // If the request contains 'ajaxinitialize', calls the ajaxInitialize function
                        DEBUG_SERVERLN(F("Sto facendo l'ajax")); // that sends the parameters to the client
                        ServerEncoder::ajaxInitialize(client);
                        break;
                    }
                    else if (webGetString.indexOf("ajaxupdatediag") >= 0)
                    { // If the request contains 'ajaxupdatediag', calls ajaxUpdateDiag function
                        DEBUG_SERVERLN(F("Sto mandando diagnostica"));
                        ServerEncoder::ajaxUpdateDiag(client);
                        break;
                    }

                    else if (webGetString.indexOf("ajaxreset") >= 0)
                    { // If the request contains 'ajaxreset', sets the memory "restartNeeded" that will cause a device reset
                        DEBUG_SERVERLN(F("Reset request received"));
                        client.print(F("Ok"));
                        restartNeeded = true;
                        break;
                    }
                    else
                    { // Otherwise parses the HTTP request to store any saved parameters and shows the page
                        DEBUG_SERVERLN(F("Mostro la pagina"));
                        tempReturn = ServerEncoder::parseResponse();
                        DEBUG_SERVERLN(F("======================================="));
                        DEBUG_SERVER(F("parseResponse() return is: "));
                        DEBUG_SERVERLN(tempReturn);
                        restartNeeded = (tempReturn & 0x01) | restartNeeded;
                        transmissionNeeded = tempReturn & 0x02;
                        ServerEncoder::printPage(client);
                        break;
                    }
                }

                if (c == '\n')
                { // End of a line reached
                    currentLineIsBlank = true;
                }
                else if (c != '\r')
                { // Line is not ended
                    currentLineIsBlank = false;
                }
            }
        }

        delay(1); // Wait a moment for the page to be displayed

        client.stop();     // Stop the connection
        webGetString = ""; // Empty the HTTP request string
        DEBUG_SERVERLN(F(" - Fatto, Chiusura connessione"));

        delay(2);
        if (restartNeeded)
        { // If a reinitialization of the arduino is needed (any of the network parameters has been changed) calls the software reset function
            restartNeeded = false;
            DEBUG_SERVERLN(F("At least one critical parameter has been changed. The device will restart"));
            //delay (20);
            resetFunc();
        }
    }
    return transmissionNeeded;
}

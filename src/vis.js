var audioContext;
var canvas, canvasContext;
var analyser, audioSourceNode;
var freqBinCount, bufferSize;
var barWidth, barHeight;
var multiplier = 6;
var cutoff = 150;
var colors = [];

const WIDTH = 1200, HEIGHT = 512;

window.onload = function() {
	canvas = document.getElementById("main-canvas");
	canvasContext = canvas.getContext("2d");

	if ((window.File || window.FileReader || window.FileList || window.Blob) == false) {
		alert("Browser does not support the File API.");
	}

  while (colors.length < 100) {
    do {
        var color = Math.floor((Math.random()*1000000)+1);
    } while (colors.indexOf(color) >= 0);
    colors.push("#" + ("000000" + color.toString(16)).slice(-6));
  }
  colors = ["#21B6A8", "#CBFFFA", "#7F1917", "#FFD197"]
}

function Visualize(){
	if (audioSourceNode){
		audioSourceNode.stop();
	}
	audioContext = new AudioContext();
	var input = document.getElementById("audio-file");
	var file = input.files[0];
	var fr = new FileReader();
	fr.readAsArrayBuffer(file);
	fr.onload = function() {
			var audioData = fr.result;
			console.log(audioData);
			audioContext.decodeAudioData(audioData).then(function(decodedData) {
				console.log(decodedData);
				audioSourceNode = new AudioBufferSourceNode(audioContext);
				audioSourceNode.buffer = decodedData;
				audioSourceNode.start();
				AnalyseAudio(audioSourceNode);
		});
	}
}

function AnalyseAudio(audioSourceNode) {
	bufferSize = 4096;
	freqBinCount = bufferSize / 2;
	analyser = new AnalyserNode(audioContext);
	analyser.fftSize = bufferSize;
	analyser.smoothingTimeConstant = 0.85;

	audioSourceNode.connect(analyser);
	analyser.connect(audioContext.destination);

	console.log(analyser);
	dataArray = new Float32Array(bufferSize / 2);
	window.requestAnimationFrame(Draw);
}

function Draw() {

  // d3 = require("d3@6")

  // const colorScale = d3.scale.category10();

	window.requestAnimationFrame(Draw);
	analyser.getFloatFrequencyData(dataArray);
	// canvasContext.fillStyle = "#33cc33";
	barWidth = (WIDTH / freqBinCount)*10;
	var x = 0;
	canvasContext.clearRect(0, 0, WIDTH, HEIGHT);
	for (var i = 0; i < freqBinCount; i++) {
		barHeight = ((256 + dataArray[i]) - cutoff) * multiplier;
		canvasContext.fillRect(x, HEIGHT - barHeight, barWidth, barHeight);
    	canvasContext.fillStyle = 'rgb(' + (Math.floor((barHeight/HEIGHT)*255)) + ', ' +(Math.floor((barHeight/HEIGHT)*255)) + ', ' + (Math.floor((barHeight/HEIGHT)*255)) +')';
		x += barWidth;
	}
}

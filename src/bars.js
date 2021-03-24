const WIDTH = 1200, HEIGHT = 512;

export const drawBars = function(analyser) {
	window.requestAnimationFrame(Draw);
	analyser.getFloatFrequencyData(dataArray);
	canvasContext.fillStyle = "#33cc33";
	barWidth = (WIDTH / freqBinCount)*2;
	var x = 0;
	canvasContext.clearRect(0, 0, WIDTH, HEIGHT);
	for (var i = 0; i < freqBinCount; i++) {
		barHeight = ((256 + dataArray[i]) - cutoff) * multiplier;
		canvasContext.fillRect(x, HEIGHT - barHeight, barWidth, barHeight);
		x += barWidth;
	}
}

window.onload = () => {
  // register button from html page
  var buttonElement = document.getElementById('play');
  // Set up audio context
  window.AudioContext = window.AudioContext || window.webkitAudioContext;

  const audioContext = new AudioContext();
  let currentBuffer = null;

  // start visualizer on click of button
  buttonElement.onclick = function() {
    getAudioContext().resume();
  }

  const visualizeAudio = url => {
    fetch(url)
      .then(response => response.arrayBuffer())
      .then(arrayBuffer => audioContext.decodeAudioData(arrayBuffer))
      .then(audioBuffer => visualize(audioBuffer));
  };

  const filterData = audioBuffer => {
    const rawData = audioBuffer.getChannelData(0); // We only need to work with one channel of data
    const samples = 70; // Number of samples we want to have in our final data set
    const blockSize = Math.floor(rawData.length / samples); // the number of samples in each subdivision
    const filteredData = [];
    for (let i = 0; i < samples; i++) {
      let blockStart = blockSize * i; // the location of the first sample in the block
      let sum = 0;
      for (let j = 0; j < blockSize; j++) {
        sum = sum + Math.abs(rawData[blockStart + j]) // find the sum of all the samples in the block
      }
      filteredData.push(sum / blockSize); // divide the sum by the block size to get the average
    }
    return filteredData;
  }

  const normalizeData = filteredData => {
    const multiplier = Math.pow(Math.max(...filteredData), -1);
    return filteredData.map(n => n * multiplier);
  }

  const draw = normalizedData => {
    // Set up the canvas
    const canvas = document.querySelector("canvas");
    const dpr = window.devicePixelRatio || 1;
    const padding = 20;
    canvas.width = canvas.offsetWidth * dpr;
    canvas.height = (canvas.offsetHeight + padding * 2) * dpr;
    const ctx = canvas.getContext("2d");
    ctx.scale(dpr, dpr);
    ctx.translate(0, canvas.offsetHeight / 2 + padding); // Set Y = 0 to be in the middle of the canvas

    // draw the line segments
    const width = canvas.offsetWidth / normalizedData.length;
    for (let i = 0; i < normalizedData.length; i++) {
      const x = width * i;
      let height = normalizedData[i] * canvas.offsetHeight - padding;
      if (height < 0) {
          height = 0;
      } else if (height > canvas.offsetHeight / 2) {
          height = height > canvas.offsetHeight / 2;
      }
      drawLineSegment(ctx, x, height, width, (i + 1) % 2);
    }
  };
}

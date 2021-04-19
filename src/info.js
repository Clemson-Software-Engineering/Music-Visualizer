const fs = require('fs')
const axios = require("axios")
const SpotifyWebApi = require('spotify-web-api-node');
const { stringify } = require('querystring');
const token = "BQDz_eBMI7OsB_OoU-5XL3fmekCQBKCh8TggunXpRaHiOw0-0raLitO-IUatceC8SBttS9Z9F5xSjWF9IkT7HOgIBKV0Hu8u2ViQGhS2IE36qJJ7gacD3JfFcv6RFj7SvJrg5AfYwhHVA4ai8ry98FQhsJJIsLHR8M_pFdRwfzxMR2xRG67ngsS_dCPzvu1MtJqF_aqP7JAkjJpE5ksjKuRxuo6ZD6MXg1A1y19X3qJAcLkDlA0I0W3rg22SLHpzeULISKbIGzy1eKWHvcGgYe316TM";
accessToken = "Bearer"
const spotifyApi = new SpotifyWebApi();
spotifyApi.setAccessToken(token);

//GET MY PROFILE DATA
function getMyData() {
  (async () => {
    const me = await spotifyApi.getMe();
    // console.log(me.body);
    getMyCurrentPlayingTrack(me.body.id);

  })().catch(e => {
    console.error(e);
  });
}

async function getMyCurrentPlayingTrack(userName) {
   albumID = null
    const data = await spotifyApi.getMyCurrentPlayingTrack()
    .then(function(data) {
      albumID = data.body.item.album.id
      str = stringify(data)
    }, function(err) {
      console.log('Something went wrong!', err);
    });
    
    let url = 'https://api.spotify.com/v1/albums/'+albumID+'?market=FI'

    axios.get(url, {
      headers: {
        "Authorization": "Bearer " + token
      }
      })
      .then((res) => {
        console.log(res.data)
        console.log("++++++_____________+++++++++++++______")
        console.log(res.data.artists[0].name)
        console.log(res.data.images[0].url)
      })
      .catch((error) => {
        console.error(error)
      })
    console.log("+++++++++++++++++++++++++++++++++++++")

  }

  // async function getCurrentTrackAlbum(userName) {
  //   const data = await spotifyApi.getAlbum()
  //   .then(function(data) {
  //     console.log('Song Image: ' + data.body.image[0]);
  //   }, function(err) {
  //     console.log('Something went wrong!', err);
  //   });
  // GET https://api.spotify.com/v1/shows/2yB9jTRog4XGCKG5bpNZUA?market=FI
  //   console.log("+++++++++++++++++++++++++++++++++++++")
  // }
getMyData();
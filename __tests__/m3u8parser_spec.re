let plist = {|
#EXTM3U

#EXT-X-MEDIA:TYPE=AUDIO,GROUP-ID="stereo",LANGUAGE="en",NAME="English",DEFAULT=YES,AUTOSELECT=YES,URI="audio/stereo/en/128kbit.m3u8"
#EXT-X-MEDIA:TYPE=AUDIO,GROUP-ID="stereo",LANGUAGE="dubbing",NAME="Dubbing",DEFAULT=NO,AUTOSELECT=YES,URI="audio/stereo/none/128kbit.m3u8"

#EXT-X-MEDIA:TYPE=AUDIO,GROUP-ID="surround",LANGUAGE="en",NAME="English",DEFAULT=YES,AUTOSELECT=YES,URI="audio/surround/en/320kbit.m3u8"
#EXT-X-MEDIA:TYPE=AUDIO,GROUP-ID="surround",LANGUAGE="dubbing",NAME="Dubbing",DEFAULT=NO,AUTOSELECT=YES,URI="audio/stereo/none/128kbit.m3u8"

#EXT-X-MEDIA:TYPE=SUBTITLES,GROUP-ID="subs",NAME="Deutsch",DEFAULT=NO,AUTOSELECT=YES,FORCED=NO,LANGUAGE="de",URI="subtitles_de.m3u8"
#EXT-X-MEDIA:TYPE=SUBTITLES,GROUP-ID="subs",NAME="English",DEFAULT=YES,AUTOSELECT=YES,FORCED=NO,LANGUAGE="en",URI="subtitles_en.m3u8"
#EXT-X-MEDIA:TYPE=SUBTITLES,GROUP-ID="subs",NAME="Espanol",DEFAULT=NO,AUTOSELECT=YES,FORCED=NO,LANGUAGE="es",URI="subtitles_es.m3u8"
#EXT-X-MEDIA:TYPE=SUBTITLES,GROUP-ID="subs",NAME="Français",DEFAULT=NO,AUTOSELECT=YES,FORCED=NO,LANGUAGE="fr",URI="subtitles_fr.m3u8"

#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=258157,CODECS="avc1.4d400d,mp4a.40.2",AUDIO="stereo",RESOLUTION=422x180,SUBTITLES="subs"
video/250kbit.m3u8
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=520929,CODECS="avc1.4d4015,mp4a.40.2",AUDIO="stereo",RESOLUTION=638x272,SUBTITLES="subs"
video/500kbit.m3u8
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=831270,CODECS="avc1.4d4015,mp4a.40.2",AUDIO="stereo",RESOLUTION=638x272,SUBTITLES="subs"
video/800kbit.m3u8
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=1144430,CODECS="avc1.4d401f,mp4a.40.2",AUDIO="surround",RESOLUTION=958x408,SUBTITLES="subs"
video/1100kbit.m3u8
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=1558322,CODECS="avc1.4d401f,mp4a.40.2",AUDIO="surround",RESOLUTION=1277x554,SUBTITLES="subs"
video/1500kbit.m3u8
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=4149264,CODECS="avc1.4d4028,mp4a.40.2",AUDIO="surround",RESOLUTION=1921x818,SUBTITLES="subs"
video/4000kbit.m3u8
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=6214307,CODECS="avc1.4d4028,mp4a.40.2",AUDIO="surround",RESOLUTION=1921x818,SUBTITLES="subs"
video/6000kbit.m3u8
#EXT-X-STREAM-INF:PROGRAM-ID=1,BANDWIDTH=10285391,CODECS="avc1.4d4033,mp4a.40.2",AUDIO="surround",RESOLUTION=4096x1744,SUBTITLES="subs"
video/10000kbit.m3u8
|};

open Jest;

let () =
  describe(
    "m38u-parser",
    ExpectJs.(
      () => {
        test("#make", () =>
          expect(M3u8Parser.make()) |> toBeTruthy
        );

        test("#push", () =>
          expect(M3u8Parser.make() |> M3u8Parser.push("Hey")) |> toBeTruthy
        );

        test("#end", () =>
          expect(M3u8Parser.make() |> M3u8Parser.end_) |> toBeTruthy
        );

        test("#manifest", () =>
          expect(M3u8Parser.make() |> M3u8Parser.manifestGet) |> toBeTruthy
        );

        test("#manifest#allowCache", () => {
          let manifest = M3u8Parser.make() |> M3u8Parser.manifestGet;
          expect(manifest##allowCache) |> toEqual(true);
        });

        test("#manifest#mediaGroups undefined group", () => {
          let manifest =
            M3u8Parser.make()
            |> M3u8Parser.push(plist)
            |> M3u8Parser.end_
            |> M3u8Parser.manifestGet;

          expect(
            switch (manifest##mediaGroups) {
            | Some(group) => Js.Dict.get(group, "Hey")
            | None => None
            },
          )
          |> toBeFalsy;
        });

        test("#manifest#mediaGroups AUDIO group", () => {
          let manifest =
            M3u8Parser.make()
            |> M3u8Parser.push(plist)
            |> M3u8Parser.end_
            |> M3u8Parser.manifestGet;

          expect(
            switch (manifest##mediaGroups) {
            | Some(group) => Js.Dict.get(group, "AUDIO")
            | None => None
            },
          )
          |> toBeTruthy;
        });
      }
    ),
  );
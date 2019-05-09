# rosary

A Rosary web app written in ReasonML and React.

https://scott-fleischman.github.io/rosary

## Local testing
```sh
yarn
yarn build
yarn webpack
```

In another terminal:
```
yarn server
```

Point browser at [127.0.0.1:8000](http://127.0.0.1/)

## Deploy
Prerequisites: Create a peer-level clone named `rosary-publish`. Switch to `gh-pages` branch.
```sh
git clone git@github.com:scott-fleischman/rosary.git rosary-publish
git checkout gh-pages
```

So your directory structure should look like:
```
.../rosary
.../rosary-publish
```

In the `rosary` clone (`master` branch), run the build script which does a production build and copies everything into `../rosary-publish`
```sh
cd rosary
./build-publish.sh
```

In the `rosary-publish` (`gh-pages` branch), commit the changes and push.
```sh
cd rosary-publish
git add .
git status
git commit -m "Update website"
git push origin gh-pages
```

#!/bin/bash -x

yarn build

rm -rf build
yarn run webpack:production

rm -rf ../rosary-publish/*
cp -vR build/* ../rosary-publish

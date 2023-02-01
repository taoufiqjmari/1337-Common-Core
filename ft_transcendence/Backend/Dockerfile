FROM node:18.13.0-alpine

RUN mkdir -p /usr/src/app
WORKDIR /usr/src/app

COPY . .
RUN npm ci

RUN npm run build

CMD ["sh", "run-prisma-and-start.sh"]

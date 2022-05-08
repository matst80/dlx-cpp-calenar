FROM nginx
WORKDIR /usr/share/nginx/html
COPY test.* ./
COPY index.html .
COPY nginx.conf /etc/nginx/conf.d/default.conf
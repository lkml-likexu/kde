#!/bin/bash
cat caixin_rss_feeds.opml| grep -owP "xmlUrl=\".*?\"" | awk -F '"' '{print $2}' | sort | uniq > caixin_blog_feeds.txt
# -*- coding: utf-8 -*-

# @Author  : my honey Thea
# 在命令行中运行 python3 millionaire-hero.py
# 我们会运行三个方法帮助你作出决策，方法一是直接在百度中搜索问题
# 方法二和方法三 选 绿色项 即可
# @Time    : 2018/1/9 10:39
# @desc    :
# TODO: error:  Expecting value: line 1 column 1 (char 0)

import requests
import webbrowser
import urllib.parse
import re
import time

# # 颜色兼容 Win 10
from colorama import init,Fore
init()

# http://conf.jiecaojingxuan.com/config/app
config_url = 'http://conf.jiecaojingxuan.com/config/app'
# problem_url = 'http://htpmsg.jiecaojingxuan.com/msg/current'
default_url = 'http://msg.api.chongdingdahui.com/msg/current'
problem_url = '/msg/current'
# problem_url = ''

questions = {}

response = [
    {"code":0,"msg":"no data"},
    {"code":0,"msg":"成功","data":{"event":{""}}},
    {"code":0,"msg":"成功","data":{"event":{"answerTime":10,"correctOption":0,"desc":"12.李清照的《如梦令》里的“绿肥红瘦”是描写什么季节的景象？","displayOrder":11,"liveId":106,"options":"[\"晚春\",\"盛夏\",\"初秋\"]","questionId":1221,"showTime":1515762793422,"stats":[8061,6262,6557],"status":2,"type":"showAnswer"},"type":"showAnswer"}},
    {"code":0,"msg":"成功","data":{"event":{"answerTime":10,"correctOption":2,"desc":"11.1980年的今天，湖南岳阳捕获了一条活体白鱀豚，经过人工饲养又存活了多少年？","displayOrder":10,"liveId":106,"options":"[\"12年\",\"15年\",\"22年\"]","questionId":1220,"showTime":1515762704717,"stats":[15243,23408,15460],"status":2,"type":"showAnswer"},"type":"showAnswer"}},
    {"code":0,"msg":"成功","data":{"event":{"answerTime":10,"correctOption":2,"desc":"10.目前亚洲迪士尼乐园中占地面积最大的是？","displayOrder":9,"liveId":106,"options":"[\"东京迪士尼乐园\",\"香港迪士尼乐园\",\"上海迪士尼乐园\"]","questionId":1219,"showTime":1515762646646,"stats":[13483,12353,51322],"status":2,"type":"showAnswer"},"type":"showAnswer"}},
    {"code":0,"msg":"成功","data":{"event":{"answerTime":10,"desc":"10.目前亚洲迪士尼乐园中占地面积最大的是？","displayOrder":9,"liveId":106,"options":"[\"东京迪士尼乐园\",\"香港迪士尼乐园\",\"上海迪士尼乐园\"]","questionId":1219,"showTime":1515762612476,"status":0,"type":"showQuestion"},"type":"showQuestion"}},
    {"code":0,"msg":"成功","data":{"event":{"answerTime":10,"correctOption":1,"desc":"9.中国别称“榕城”的是？","displayOrder":8,"liveId":106,"options":"[\"四川成都\",\"福建福州\",\"广东广州\"]","questionId":1218,"showTime":1515762592766,"stats":[51663,67275,18106],"status":2,"type":"showAnswer"},"type":"showAnswer"}},
    {"code":0,"msg":"成功","data":{"event":{"answerTime":10,"correctOption":0,"desc":"8.书本《我的前半生》是由哪位清朝皇帝撰写的自传？","displayOrder":7,"liveId":106,"options":"[\"爱新觉罗·溥仪\",\"爱新觉罗·载湉\",\"爱新觉罗·载淳\"]","questionId":1217,"showTime":1515762532678,"stats":[135680,7184,7492],"status":2,"type":"showAnswer"},"type":"showAnswer"}},
    {"code":0,"msg":"成功","data":{"event":{"answerTime":10,"correctOption":1,"desc":"7.周星驰的御用中文配音演员是？","displayOrder":6,"liveId":106,"options":"[\"边江\",\"石班瑜\",\"童自荣\"]","questionId":1216,"showTime":1515762469463,"stats":[15443,144676,29908],"status":2,"type":"showAnswer"},"type":"showAnswer"}},
    {"code":0,"msg":"成功","data":{"event":{"answerTime":10,"correctOption":2,"desc":"6.“玄武门之变”中，杀死李建成的是？","displayOrder":5,"liveId":106,"options":"[\"李渊\",\"李元吉\",\"李世民\"]","questionId":1215,"showTime":1515762393519,"stats":[22554,23723,183775],"status":2,"type":"showAnswer"},"type":"showAnswer"}},
    {"code":0,"msg":"成功","data":{"event":{"answerTime":10,"correctOption":2,"desc":"6.“玄武门之变”中，杀死李建成的是？","displayOrder":5,"liveId":106,"options":"[\"李渊\",\"李元吉\",\"李世民\"]","questionId":1215,"showTime":1515762393519,"stats":[22554,23723,183775],"status":2,"type":"showAnswer"},"type":"showAnswer"}}
]

def open_webbrowser(question):
    print('\n-- 方法1： 请优先查看浏览器中的百度查询结果 --\n')
    webbrowser.open('https://baidu.com/s?wd=' + urllib.parse.quote(question))

def open_webbrowser_count(question,choices):
    print('\n-- 方法2： 题目+选项搜索结果计数法 --\n')
    if '不是' in question:
        print('**请注意此题为否定题,选计数最少的**')

    counts = []
    for i in range(len(choices)):
        # 请求
        req = requests.get(url='http://www.baidu.com/s', params={'wd': question + choices[i]})
        content = req.text
        index = content.find('百度为您找到相关结果约') + 11
        content = content[index:]
        index = content.find('个')
        count = content[:index].replace(',', '')
        counts.append(count)
        #print(choices[i] + " : " + count)
    output(choices, counts)

def count_base(question,choices):
    print('\n-- 方法3： 题目搜索结果包含选项词频计数法 --\n')
    # 请求
    req = requests.get(url='http://www.baidu.com/s', params={'wd':question})
    content = req.text
    #print(content)
    counts = []
    if '不是' in question:
        print('**请注意此题为否定题,选计数最少的**')
    for i in range(len(choices)):
        counts.append(content.count(choices[i]))
        #print(choices[i] + " : " + str(counts[i]))
    output(choices, counts)

def output(choices, counts):
    counts = list(map(int, counts))
    #print(choices, counts)

    # 计数最高
    index_max = counts.index(max(counts))

    # 计数最少
    index_min = counts.index(min(counts))

    if index_max == index_min:
        print(Fore.RED + "高低计数相等此方法失效！" + Fore.RESET)
        return

    for i in range(len(choices)):
        print()
        if i == index_max:
            # 绿色为计数最高的答案
            print(Fore.GREEN + "{0} : {1} ".format(choices[i], counts[i]) + Fore.RESET)
        elif i == index_min:
            # 红色为计数最低的答案
            print(Fore.MAGENTA + "{0} : {1}".format(choices[i], counts[i]) + Fore.RESET)
        else:
            print("{0} : {1}".format(choices[i], counts[i]))


def run_algorithm(al_num, question, choices):
    if al_num == 0:
        open_webbrowser(question)
    elif al_num == 1:
        open_webbrowser_count(question, choices)
    elif al_num == 2:
        count_base(question, choices)

def getProblemUrl(session, url):
    try :
        config = session.get(url).json()
        host = config['data']['messageHosts'][0]
        return host + problem_url
    except:
        return default_url

def formatProblem(problem): 
    index = problem.find('.')
    if (index != -1):
        problem = problem[index + 1 :]
    return problem; 

def formatOptions(choices):
    return re.findall('"(.*?)"', choices)  

def request(session, url):
    try :
        result = session.get(url).json()
        if (result and result.__contains__('data')):
            desc = formatProblem(result['data']['event']['desc'])
            options = formatOptions(result['data']['event']['options'])
            if (not questions.__contains__(desc)):   
                print('\n问题：' + desc + '\n')
                run_algorithm(0, desc, options)
                run_algorithm(1, desc, options)
                run_algorithm(2, desc, options)
                questions[desc] = '1'
        else:
            print(result)
    except Exception as e:
        print('error: ', e)


if __name__ == '__main__':
    session = requests.session()
    session.headers.update({
        'User-Agent': 'Mozilla/5.0 (Linux; U; Android 7.0; zh-cn; MI 5 Build/NRD90M) AppleWebKit/534.30 (KHTML, like Gecko) Version/4.0 Mobile Safari/534.30',
        'X-Live-App-Version': '1.1.3',
        'X-Live-Device-Type': 'android',
        'X-Live-Session-Token': '1.19373008.2388600.pQR.02240f45b33c0284955eaf4f9c3fb20f'
    })
    print('** 请注意答题时间 **')
    problemUrl = getProblemUrl(session, config_url)
    # problemUrl = default_url
    print('** 当前拉取题目路径：' + problemUrl)
    print('** 正在拼命拉取题目，请稍后...')
    while (1):
        request(session, problemUrl)
        time.sleep(1)

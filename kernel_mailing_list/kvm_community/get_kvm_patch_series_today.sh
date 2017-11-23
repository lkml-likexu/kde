#!/bin/bash $1
set -e
# demo: sh get_kvm_patch_today.sh -d 2018-10-09

while getopts "d:" arg #选项后面的冒号表示该选项需要参数
do
    case $arg in
        d)
        echo "a's arg:$OPTARG" #参数存在$OPTARG中
        if  [ ! -n "$1" ] ;then
            DATE=`date +"%Y-%m-%d"`
        else
            DATE=$OPTARG
        fi
        echo "check kvm-mailing-list on ${DATE}"

        rm -rf ${DATE}
        mkdir ${DATE}
        
        cd ${DATE}
        if [ ! -f "${DATE}.json" ]; then 
            wget "https://patchwork.kernel.org/api/series/?project=8&archive=both&format=json&before=${DATE}T23%3A59%3A59&since=${DATE}T00%3A00%3A00" -O ${DATE}.json
        fi
        
        num=`cat ${DATE}.json | jq '. | length'`
        if [ ${num} -eq 0 ]
        then
            echo "${DATE} is NULL"
            cd .. 
            rm -rf ${DATE}
            exit
        fi

        cat ${DATE}.json | jq '.[]' | jq '.id' | while read var
        do
            if [ ! -d "${var}" ]; then 
                mkdir ${var}
            fi
            cd ${var}
            if [ ! -f "series_${var}.json" ]; then 
                wget "https://patchwork.kernel.org/api/series/${var}/?format=json&archive=both" -O series_${var}.json
            fi

            new_name=`cat series_${var}.json | jq -r '.name' | sed "s/\[//g" | sed "s/\]//g" | sed "s/://g" | sed "s/\///g" | sed "s/ /_/g"`
            if [ "$new_name" = "null" ] ; then 
                echo "Subject name is null" 
                new_name=`cat series_${var}.json | jq -r '.submitter.name' | sed "s/\[//g" | sed "s/\]//g" | sed "s/://g" | sed "s/\///g" | sed "s/ /_/g"`
            fi
            
            cd ..
            mv ${var} ${new_name}_${var}
            cd ${new_name}_${var}

            num=`cat series_${var}.json | jq '. | length'`
            if [ ${num} -eq 0 ]
            then
                echo "series_${var}.json is NULL"
                cd .. 
                rm -rf ${var}
                exit
            fi

            mbox=`cat series_${var}.json | jq -r '.mbox'`
            wget "$mbox" -O series_${var}.patch

            if [ -f "wget-log" ]; then 
                rm wget-log
                exit
            fi
            cd ..

            FILE="overview_series_${DATE}.md"
            if [ -f "${FILE}" ]; then 
            rm ${FILE}
            fi
            touch ${FILE}

            for var in `ls -1 */*.patch`
            do 
                FLINE=`cat ${var} | grep -n -m 1 "X-Virus-Scanned: ClamAV using ClamSMTP" | head -n1 | awk -F ':' '{ print $1 }'`
                TLINE=`cat ${var} | grep -n -m 1 "\-\-\- a" | head -n1 | awk -F ':' '{ print $1 }'`
                NAME=`cat ${var} | grep  -m 1 "From: " | head -n1`
                SUBJECT=`cat ${var} | grep -m 1 "Subject: " | head -n1 | sed 's/Subject: //g'`
                SUBLINE=`cat ${var} | grep -n -m 1 "Subject: " | head -n1 | awk -F ':' '{ print $1 }'`
                k=`expr ${SUBLINE} + 1`
                IF=`sed -n "${k}p" ${var}`

                a=`echo ${IF} | grep -v "Date: " | grep -v "Message-ID:" | wc -l`
                if [ ${a} -eq 1 ]
                then
                    echo "#### ${SUBJECT}${IF}" >> ${FILE}
                else
                    echo "#### ${SUBJECT}" >> ${FILE}
                fi
                echo "##### ${NAME}\n" >> ${FILE}
                echo "\`\`\`c" >> ${FILE}
                f=`expr ${FLINE} + 2`
                b=`cat ${var} | grep -n -m 1 "\-\-\- a" | wc -l`
                if [ ${b} -eq 0 ]
                then
                    t=`cat ${var} | wc -l`
                else
                    t=`expr ${TLINE} - 3`
                fi
                sed -n -e "${f},${t}p" ${var}  >> ${FILE}
                # tail -n +${k} ${var} >> ${FILE}
                echo "\`\`\`" >> ${FILE}
            done

            # cover_letter
            wget "https://patchwork.kernel.org/api/covers/?project=8&format=json&archive=both&before=${DATE}T23%3A59%3A59&since=${DATE}T00%3A00%3A00" -O covers.json
        
            num=`cat covers.json | jq '. | length'`
            if [ ${num} -eq 0 ]
            then
                echo "${DATE} is NULL"
                cd .. 
                exit
            fi

            cat covers.json | jq '.[]' | jq '.id' | while read q
            do
                if [ ! -f "${q}.patch" ]; then 
                    wget "https://patchwork.kernel.org/cover/${q}/mbox/" -O ${q}.patch
                fi
            done

            FILE="overview_covers_${DATE}.md"
            if [ -f "${FILE}" ]; then 
            rm ${FILE}
            fi
            touch ${FILE}
            echo "\n" >> ${FILE}
            # i=1
            for w in `ls -1 *.patch`
            do 
            LINE=`cat ${w} | grep -n "X-Virus-Scanned" | awk -F ':' '{ print $1 }'`
            NAME=`cat ${w} | grep "From: "`
            SUBJECT=`cat ${w} | grep "Subject: " | sed 's/Subject: //g'`
            echo "#### ${SUBJECT}" >> ${FILE}
            echo "##### ${NAME}\n" >> ${FILE}
            echo "\`\`\`c" >> ${FILE}
            k=`expr ${LINE} + 1`
            tail -n +${k} ${w} >> ${FILE}
            echo "\`\`\`" >> ${FILE}
            # i=`expr $i + 1`
            done
            # rm *.patch
        done
        cd ..
        ;;
        ?)  #当有不认识的选项的时候arg为?
        echo "unkonw argument"
    exit 1
    ;;
    esac
done

# cat *.patch | grep "Subject: " > patches.list
# sed 's/Subject: /* /g' patches.list | sort -k 3 -r >> ${FILE}
# cat */*.json | jq '.[] | { Patch: .name, From: .submitter.name, Email: .submitter.email}'
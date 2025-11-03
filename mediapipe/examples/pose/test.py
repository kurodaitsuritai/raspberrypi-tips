import sys
import json
import cv2
import mediapipe as mp
mp_drawing = mp.solutions.drawing_utils
mp_pose = mp.solutions.pose

def estimate_pose(file):
    landmarks = [
        'NOSE', 'LEFT_EYE_INNER', 'LEFT_EYE', 'LEFT_EYE_OUTER', 'RIGHT_EYE_INNER', 
        'RIGHT_EYE', 'RIGHT_EYE_OUTER', 'LEFT_EAR', 'RIGHT_EAR', 'MOUTH_LEFT', 'MOUTH_RIGHT', 
        'LEFT_SHOULDER', 'RIGHT_SHOULDER', 'LEFT_ELBOW', 'RIGHT_ELBOW', 'LEFT_WRIST', 'RIGHT_WRIST', 
        'LEFT_PINKY', 'RIGHT_PINKY', 'LEFT_INDEX', 'RIGHT_INDEX', 'LEFT_THUMB', 'RIGHT_THUMB', 'LEFT_HIP', 
        'RIGHT_HIP', 'LEFT_KNEE', 'RIGHT_KNEE', 'LEFT_ANKLE', 'RIGHT_ANKLE', 'LEFT_HEEL', 'RIGHT_HEEL', 
        'LEFT_FOOT_INDEX', 'RIGHT_FOOT_INDEX' ]
    
    with mp_pose.Pose(static_image_mode=True, min_detection_confidence=0.5) as pose:
        image = cv2.imread(file)
        image_height, image_width, _ = image.shape
        results = pose.process(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))

        res = {'errcode': 0}

        if results.pose_landmarks:
            res['errcode'] = 0
            for index, landmark in enumerate(landmarks):
                x = results.pose_landmarks.landmark[index].x * image_width
                y = results.pose_landmarks.landmark[index].y * image_height
                z = results.pose_landmarks.landmark[index].z
                visibility = results.pose_landmarks.landmark[index].visibility
                # print(f'{landmark} - {x}, {y}, {z}, {visibility}')
                res[landmarks[index]] = [index, x, y, z, visibility]
            # 画像にポーズのランドマークを描画
            #annotated_image = image.copy()
            #mp_drawing.draw_landmarks(annotated_image, results.pose_landmarks, mp_pose.POSE_CONNECTIONS)
            #cv2.imwrite('annotated_image.png', annotated_image)
        else:
            res['errcode']= 1
            
        return res

if __name__ == '__main__':
    args = sys.argv
    ret={}
    if 2 == len(args):
        file = args[1]
        res = estimate_pose(file)
        ret = {'pose_num':1, 'poses':[res]}
    elif 3 == len(args):
        file1 = args[1]
        file2 = args[2]
        res1 = estimate_pose(file1)
        res2 = estimate_pose(file2)
        ret = {'pose_num':2, 'poses':[res1, res2]}

    print(json.dumps(ret, indent=4))

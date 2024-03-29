/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * License); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * AS IS BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Copyright (c) 2018, Open AI Lab
 * Author: chunyinglv@openailab.com
 *
 * 20180910     Modified by minglu@openailab.com for EAIDK
 */
#ifndef __MTCNN_HPP__
#define __MTCNN_HPP__



#include "mtcnn_utils.hpp"


class mtcnn {
public:
    int minsize_;
    float conf_p_threshold_;
    float conf_r_threshold_;
    float conf_o_threshold_;

    float nms_p_threshold_;
    float nms_r_threshold_;
    float nms_o_threshold_;

    mtcnn(	int minsize=60,
            float conf_p=0.6,float conf_r=0.7,float conf_o=0.8,
            float nms_p=0.5,float nms_r=0.7,float nms_o=0.7);
    ~mtcnn()
    {
 	destroy_runtime_graph(PNet_graph);
	destroy_runtime_graph(RNet_graph);
	destroy_runtime_graph(ONet_graph);
	remove_model(PNet_model_name);
	remove_model(RNet_model_name);
	remove_model(ONet_model_name);
    };

    int load_3model(const std::string& model_dir);

    void detect(fcv::Mat& img,std::vector<face_box>& face_list);

protected:
    int run_PNet(const fcv::Mat& img, scale_window& win, std::vector<face_box>& box_list);
    int run_RNet(const fcv::Mat& img, std::vector<face_box>& pnet_boxes, std::vector<face_box>& output_boxes);
    int run_ONet(const fcv::Mat& img, std::vector<face_box>& rnet_boxes, std::vector<face_box>& output_boxes);

private:
    const char * PNet_model_name="PNet";
    const char * RNet_model_name="RNet";
   const char * ONet_model_name="ONet";
//    const char * PNet_model_name="";
//    const char * RNet_model_name="";
//    const char * ONet_model_name="";
    graph_t PNet_graph;
    graph_t RNet_graph;
    graph_t ONet_graph;
};



#endif

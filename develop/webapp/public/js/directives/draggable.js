/*
 * ngasp, a computational solution for performing next generation analysis of 
 * sequence polymorphisms using NGS data.
 * Copyright (c) 2015-2016, Sebastián Ramos Onsins and Gonzalo Vera Rodríguez,
 * Centre for Research in Agricultural Genomics.
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version
 * 2.1 as published by the Free Software Foundation.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 2.1 for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License version 2.1 along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street - Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */
// http://blog.parkji.co.uk/2013/08/11/native-drag-and-drop-in-angularjs.html

CRAG.directive('draggable', function() {
    return function(scope, element) {
        // this gives us the native JS object
        var el = element[0];

        el.draggable = true;

        el.addEventListener(
            'dragstart',
            function(e) {
                e.dataTransfer.effectAllowed = 'move';
                e.dataTransfer.setData('Text', this.id);
                //this.classList.add('drag');
                return false;
            },
            false
        );

        el.addEventListener(
            'dragend',
            function(e) {
                //this.classList.remove('drag');
                return false;
            },
            false
        );

    }
});

CRAG.directive('droppable', function() {
    return {
        scope: {
            drop: '&', // parent
            bin: '=' // bi-directional scope
        },
        link: function(scope, element) {
            // again we need the native object
            var el = element[0];

            el.addEventListener(
                'dragenter',
                function(e) {
                    //this.classList.add('over');
                    return false;
                },
                false
            );

            el.addEventListener(
                'dragleave',
                function(e) {
                    //this.classList.remove('over');
                    return false;
                },
                false
            );

            el.addEventListener(
                'dragover',
                function(e) {
                    e.dataTransfer.dropEffect = 'move';
                    // allows us to drop
                    if (e.preventDefault) {
                        e.preventDefault();
                    }
                    //this.classList.add('over');
                    return false;
                },
                false
            );

            el.addEventListener(
                'drop',
                function(e) {
                    // Stops some browsers from redirecting.
                    if (e.stopPropagation) { e.stopPropagation(); }
                    if(e.preventDefault) { e.preventDefault(); }

                    //this.classList.remove('over');

                    // This removes the item from the original place
                    //var item = document.getElementById(e.dataTransfer.getData('Text'));
                    //this.appendChild(item);

                    var dest_id = this.id;
                    var item_id = e.dataTransfer.getData('Text');
                    var position = {clientX: e.clientX, clientY: e.clientY};

                    // scope.$apply("drop()");

                    // call the passed drop function
                    scope.$apply(function(scope) {
                        var fn = scope.drop();
                        if ('undefined' !== typeof fn) {
                          fn(item_id, dest_id, position);
                        }
                    });

                    return false;
                },
                false
            );
        }
    }
});


CRAG.directive('modaldraggable', function ($document) {
  "use strict";
  return function (scope, element) {
    var startX = 0,
      startY = 0,
      x = 0,
      y = 0;
     element= angular.element(document.getElementsByClassName("modal-dialog"));
     console.log("added directive");
    element.css({
      position: 'fixed',
      cursor: 'move'
    });
    
    element.on('mousedown', function (event) {
      // Prevent default dragging of selected content
      event.preventDefault();
      startX = event.screenX - x;
      startY = event.screenY - y;
      $document.on('mousemove', mousemove);
      $document.on('mouseup', mouseup);
    });

    function mousemove(event) {
      y = event.screenY - startY;
      x = event.screenX - startX;
      element.css({
        top: y + 'px',
        left: x + 'px'
      });
    }

    function mouseup() {
      $document.unbind('mousemove', mousemove);
      $document.unbind('mouseup', mouseup);
    }
  };
});


